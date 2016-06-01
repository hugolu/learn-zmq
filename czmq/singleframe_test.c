#include <czmq.h>
#include <assert.h>

int main(void) {
    zmsg_t *msg;
    zframe_t *frame;
    char *str;
    int rc;

    // create push/pull sockets
    zsock_t *push = zsock_new_push("inproc://example");
    zsock_t *pull = zsock_new_pull("inproc://example");

    // send single-frame message
    msg = zmsg_new();
    frame = zframe_new("hello", 5);
    zmsg_prepend(msg, &frame);
    assert(zmsg_size(msg) == 1);
    assert(zmsg_content_size(msg) == 5);
    rc = zmsg_send(&msg, push);
    assert(msg == NULL);
    assert(rc == 0);

    // receive single-frame message
    msg = zmsg_recv(pull);
    assert(msg);
    assert(zmsg_size(msg) == 1);
    assert(zmsg_content_size(msg) == 5);
    str = zmsg_popstr(msg);
    puts(str);
    zmsg_destroy(&msg);

    // disconnect
    zsock_destroy(&push);
    zsock_destroy(&pull);

    return 0;
}
