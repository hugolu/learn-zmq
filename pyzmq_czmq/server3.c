#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <czmq.h>

#define HCZMQ_SOCK  "tcp://*:5566"

struct host_connection {
    in_addr_t ip;
    struct connection {
        int port;
        time_t timestamp;
    } conns[3];
};
struct host_connection hc[1];
struct host_connection *ghc = hc; // global variable accessed by threads

pthread_mutex_t mutex;

struct request {
    in_addr_t ip;
    time_t timestamp;
};

int get_request(zsock_t *sock, struct request *req) {
    zmsg_t *msg;
    int size;
    char *str;
    int Y, m, d, H, M, S;
    struct tm tm;

    msg = zmsg_recv(sock);
    size = zmsg_size(msg);
    if (size != 2) {
        // something's wrong
        zmsg_destroy(&msg);
        return -1;
    }

    str = zmsg_popstr(msg);
    req->ip = inet_addr(str);

    str = zmsg_popstr(msg);
    sscanf(str, "%04d%02d%02d%02d%02d%02d", &Y, &m, &d, &H, &M, &S);
    tm.tm_year = Y - 1900;
    tm.tm_mon = m;
    tm.tm_mday = d;
    tm.tm_hour = H;
    tm.tm_min = M;
    tm.tm_sec = S;
    req->timestamp = mktime(&tm);

    zmsg_destroy(&msg);
    return 0;
}

#define INET_NTOA(IP) inet_ntoa(*(struct in_addr*)&(IP))
void *hczmq(void *ptr) {
    struct host_connection hc;
    char port[6], timestamp[16], info[25];
    struct tm *tm;
    int idx;
    int rc;

    struct request req[1];
    zmsg_t *msg;

    printf("message from main thread: %s\n", (char *)ptr);

    // setup zmq server
    zsock_t *sock = zsock_new_rep(HCZMQ_SOCK);

    while(1) {
        // recv
        rc = get_request(sock, req);
        if (rc < 0) {
            // bad request
            continue;
        }
        strftime(timestamp, 16, "%Y%m%d%H%M%S", localtime(&req->timestamp));
        printf("ip: %s, timestamp: %s\n", INET_NTOA(req->ip), timestamp);

        // retrieve host connection by ip and timestamp
        pthread_mutex_lock(&mutex);
        msg = zmsg_new();
        for (idx = 0; idx < 3; idx++) {
            sprintf(port, "%d", ghc->conns[idx].port);
            tm = localtime(&ghc->conns[idx].timestamp);
            strftime(timestamp, 16, "%Y%m%d%H%M%S", tm);
            sprintf(info, "%s:%s", port, timestamp);
            printf("  %s\n", info);
            zmsg_addmem(msg, info, strlen(info));
        }
        pthread_mutex_unlock(&mutex);

        // send
        zmsg_send(&msg, sock);
    }

    pthread_exit((void*)123);
}

int main() {
    pthread_t thread;
    time_t now;
    int idx;

    // prepare the faked information about host connections
    ghc->ip = inet_addr("192.168.1.100");
    for (idx = 0; idx < 3; idx++) {
        now = time(NULL);
        ghc->conns[idx].port = (now + idx - 2) % 65536;
        ghc->conns[idx].timestamp = (now + idx - 2);
    }

    // create a mutex
    pthread_mutex_init(&mutex, NULL);

    // create the hczmq thread
    pthread_create(&thread, NULL, hczmq, (void *)"hello world");

    // updating the faked information every seconds
    while (1) {
        pthread_mutex_lock(&mutex);
        now = time(NULL);
        idx = now % 3;
        ghc->conns[idx].port = now % 65536;
        ghc->conns[idx].timestamp = now;
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    pthread_join(thread, NULL);

    return 0;
}
