#include "queue.h"

#include <stdlib.h>
#include <memory.h>

queue_t* queue_alloc(int capacity) {
    queue_t* queue = malloc(sizeof(queue_t));
    queue->data = malloc(capacity * sizeof(int));
    queue->size = 0;
    queue->capacity = capacity;
    queue->head = 0;
    queue->tail = -1;
    return queue;
}

queue_t* queue_copy(queue_t* queue) {
    queue_t* new_queue = queue_alloc(queue->capacity);
    memcpy(new_queue->data, queue->data, queue->capacity * sizeof(int));
    new_queue->size = queue->size;
    new_queue->head = queue->head;
    new_queue->tail = queue->tail;
    return new_queue;
}

void queue_free(queue_t** queue) {
    free((*queue)->data);
    free(*queue);
    *queue = NULL;
}

bool queue_empty(queue_t* queue) {
    return !queue->size;
}

bool queue_full(queue_t* queue) {
    return queue->size == queue->capacity;
}

int queue_size(queue_t* queue) {
    return queue->size;
}

int queue_max_size(queue_t* queue) {
    return queue->capacity;
}

bool queue_push_front(queue_t* queue, int value) {
    if (queue_full(queue)) {
        return false;
    }
    queue->head = (queue->head - 1 + queue->capacity) % queue->capacity;
    queue->data[queue->head] = value;
    ++queue->size;
    return true;
}

bool queue_push_back(queue_t* queue, int value) {
    if (queue_full(queue)) {
        return false;
    }
    queue->tail = (queue->tail + 1) % queue->capacity;
    queue->data[queue->tail] = value;
    ++queue->size;
    return true;
}

int queue_pop_front(queue_t* queue) {
    if (queue_empty(queue)) {
        return 0;
    }
    int value = queue->data[queue->head];
    queue->head = (queue->head + 1) % queue->capacity;
    --queue->size;
    return value;
}

int queue_pop_back(queue_t* queue) {
    if (queue_empty(queue)) {
        return 0;
    }
    int value = queue->data[queue->tail];
    queue->tail = (queue->tail - 1 + queue->capacity) % queue->capacity;
    --queue->size;
    return value;
}

int queue_peek_front(queue_t* queue) {
    if (queue_empty(queue)) {
        return 0;
    }
    return queue->data[queue->head];
}

int queue_peek_back(queue_t* queue) {
    if (queue_empty(queue)) {
        return 0;
    }
    return queue->data[queue->tail];
}

void queue_clear(queue_t* queue) {
    memset(queue->data, 0, queue->capacity * sizeof(int));
    queue->size = 0;
    queue->head = 0;
    queue->tail = -1;
}
