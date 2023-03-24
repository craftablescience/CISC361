#include <common.h>
#include <test.h>

test_begin()
    test_group("Pushing and popping from a queue") {
        queue_t *queue = queue_alloc(16);
        expect_true(queue_empty(queue));
        queue_push_back(queue, 10);
        expect_false(queue_empty(queue));
        expect_true(queue_size(queue) == 1);
        int value = queue_pop_front(queue);
        expect_true(value == 10);
        expect_true(queue_empty(queue));
    }
test_end()
