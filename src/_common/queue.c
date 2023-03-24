#include "queue.h"

#include <stdlib.h>
#include <memory.h>

queue_t* queue_alloc(int capacity) {
    queue_t* queue = malloc(sizeof(queue_t));
    queue->data = malloc(capacity * sizeof(int));
    queue->size = 0;
    queue->capacity = capacity;
    return queue;
}

queue_t* queue_copy(queue_t* queue) {
    queue_t* new_queue = queue_alloc(queue->capacity);
    memcpy(new_queue->data, queue->data, queue->capacity * sizeof(int));
    new_queue->size = queue->size;
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

int queue_size(queue_t* queue) {
    return queue->size;
}

int queue_max_size(queue_t* queue) {
    return queue->capacity;
}

bool queue_push_front(queue_t* queue, int value) {
    if (queue->size == queue->capacity) {
        return false;
    }
    int* tmp = malloc(queue->size * sizeof(int));
    memcpy(tmp, queue->data, queue->size * sizeof(int));
    queue->data[0] = value;
    memcpy(queue->data + 1, tmp, queue->size * sizeof(int));
    free(tmp);
    ++queue->size;
    return true;
}

bool queue_push_back(queue_t* queue, int value) {
    if (queue->size == queue->capacity) {
        return false;
    }
    queue->data[queue->size] = value;
    ++queue->size;
    return true;
}

int queue_pop_front(queue_t* queue) {
    if (!queue->size) {
        return 0;
    }
    int* tmp = malloc(queue->size * sizeof(int));
    memcpy(tmp, queue->data, queue->size * sizeof(int));
    queue->data[queue->size] = 0;
    memcpy(queue->data, tmp + 1, queue->size * sizeof(int) - sizeof(int));
    int value = tmp[0];
    free(tmp);
    --queue->size;
    return value;
}

int queue_pop_back(queue_t* queue) {
    if (!queue->size) {
        return 0;
    }
    int value = queue->data[queue->size];
    queue->data[queue->size] = 0;
    --queue->size;
    return value;
}
