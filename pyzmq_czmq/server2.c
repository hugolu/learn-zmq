#include <czmq.h>

int main(void) {
    // connect
    zsock_t *sock = zsock_new_rep("tcp://*:5566");

    // recv
    zmsg_t *msg = zmsg_recv(sock);
    int i, size = zmsg_size(msg);
    for (i = 0; i < size; i++) {
        char *string = zmsg_popstr(msg);
        puts(string);
    }
    zmsg_destroy(&msg);

    // send
    msg = zmsg_new();
    zmsg_addmem(msg, "apple", 5);
    zmsg_addmem(msg, "banana", 6);
    zmsg_addmem(msg, "cherry", 6);
    zmsg_send(&msg, sock);

    // disconnect
    zsock_destroy(&sock);
    return 0;
}
