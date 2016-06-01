#include <czmq.h>

int main(void) {
    zsock_t *push = zsock_new_push("inproc://example");
    zsock_t *pull = zsock_new_pull("inproc://example");

    zstr_send(push, "Hello, World");

    char *str = zstr_recv(pull);
    puts(str);
    zstr_free(&str);

    zsock_destroy(&push);
    zsock_destroy(&pull);
    return 0;
}
