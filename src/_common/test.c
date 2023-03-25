#include <common.h>
#include <test.h>

test(queue_push_back_pop_front) {
    queue_t* queue = queue_alloc(4);
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

test(queue_push_front_pop_back) {
    queue_t* queue = queue_alloc(4);
    expect_true(queue_empty(queue));

    queue_push_front(queue, 10);
    expect_false(queue_empty(queue));
    expect_eq(queue_size(queue), 1);

    queue_push_front(queue, 20);
    expect_eq(queue_size(queue), 2);

    int value = queue_pop_back(queue);
    expect_eq(value, 10);

    value = queue_pop_back(queue);
    expect_eq(value, 20);
    expect_true(queue_empty(queue));

    test_end();
}

test(queue_peek_clear) {
    queue_t* queue = queue_alloc(4);
    expect_true(queue_empty(queue));

    queue_push_back(queue, 10);
    expect_eq(queue_peek_front(queue), 10);
    expect_eq(queue_peek_back(queue), 10);

    queue_push_back(queue, 20);
    expect_eq(queue_peek_front(queue), 10);
    expect_eq(queue_peek_back(queue), 20);

    queue_push_back(queue, 30);
    expect_eq(queue_peek_front(queue), 10);
    expect_eq(queue_peek_back(queue), 30);

    queue_pop_front(queue);
    expect_eq(queue_peek_front(queue), 20);

    queue_clear(queue);
    expect_true(queue_empty(queue));

    test_end();
}

test(queue_use_circular_buffer) {
    queue_t* queue = queue_alloc(4);
    for (int i = 0; i < 4; i++) {
        queue_push_back(queue, i);
    }
    queue_pop_front(queue);
    queue_pop_front(queue);

    expect_eq(queue_size(queue), 2);
    queue_push_back(queue, 10);
    expect_eq(queue_size(queue), 3);

    test_end();
}

test_run(
    queue_push_back_pop_front,
    queue_push_front_pop_back,
    queue_peek_clear,
    queue_use_circular_buffer
)
