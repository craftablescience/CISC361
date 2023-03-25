#include <common.h>
#include <test.h>

test(queue_push_back_pop_front) {
    queue_t *queue = queue_alloc(16);
    expect_true(queue_empty(queue));

    queue_push_back(queue, 10);
    expect_false(queue_empty(queue));
    expect_eq(queue_size(queue), 1);

    queue_push_back(queue, 20);
    expect_eq(queue_size(queue), 2);

    int value = queue_pop_front(queue);
    expect_eq(value, 10);

    value = queue_pop_front(queue);
    expect_eq(value, 20);
    expect_true(queue_empty(queue));

    test_end();
}

test_run(
    &queue_push_back_pop_front
)
