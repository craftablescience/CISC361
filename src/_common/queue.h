#pragma once

#include <stdbool.h>

/// A simple interface over a circular buffer
typedef struct {
    int* data;
    int size;
    int capacity;
    int head;
    int tail;
} queue_t;

queue_t* queue_alloc(int capacity);

queue_t* queue_copy(queue_t* queue);

void queue_free(queue_t** queue);

bool queue_empty(queue_t* queue);

bool queue_full(queue_t* queue);

int queue_size(queue_t* queue);

int queue_max_size(queue_t* queue);

bool queue_push_front(queue_t* queue, int value);

bool queue_push_back(queue_t* queue, int value);

int queue_pop_front(queue_t* queue);

int queue_pop_back(queue_t* queue);

int queue_peek_front(queue_t* queue);

int queue_peek_back(queue_t* queue);

void queue_clear(queue_t* queue);
