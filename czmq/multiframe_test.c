#include <czmq.h>
#include <assert.h>

int main(void) {
    zmsg_t *msg;
    zframe_t *frame;
    char *str;
    int i, rc;

    // create push/pull sockets
    zsock_t *push = zsock_new_push("inproc://example");
    zsock_t *pull = zsock_new_pull("inproc://example");

    // send multi-frame message
    msg = zmsg_new();
    zmsg_addmem(msg, "apple", 5);
    zmsg_addmem(msg, "banana", 6);
    zmsg_addmem(msg, "cherry", 6);
    assert(zmsg_size(msg) == 3);
    assert(zmsg_content_size(msg) == 5+6+6);
    rc = zmsg_send(&msg, push);
    assert(msg == NULL);
    assert(rc == 0);

    // receive multi-frame message
    msg = zmsg_recv(pull);
    assert(msg);
    assert(zmsg_size(msg) == 3);
    assert(zmsg_content_size(msg) == 5+6+6);
    for (i = 0; i < 3; i++) {
        str = zmsg_popstr(msg);
        puts(str);
    }
    zmsg_destroy(&msg);

    // disconnect
    zsock_destroy(&push);
    zsock_destroy(&pull);

    return 0;
}
