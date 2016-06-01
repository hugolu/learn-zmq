#include <czmq.h>

int main(void) {
    // bind
    zsock_t *sock = zsock_new_rep("tcp://*:5566");

    // recv
    char *str = zstr_recv(sock);
    puts(str);
    zstr_free(&str);

    // send
    zstr_send(sock, "pong");

    // disconnect
    zsock_destroy(&sock);

    return 0;
}
