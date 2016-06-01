#include <czmq.h>

int main(void) {
    // connect
    zsock_t *sock = zsock_new_req("tcp://localhost:5566");

    // send
    zstr_send(sock, "ping");

    // recv
    char *str = zstr_recv(sock);
    puts(str);
    zstr_free(&str);

    // disconnect
    zsock_destroy(&sock);

    return 0;
}
