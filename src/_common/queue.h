#pragma once

#include <stdbool.h>

/*
 * A simple interface over a circular buffer -- or it would be if I actually understood math
 */

typedef struct {
    int* data;
    int size;
    int capacity;
} queue_t;

queue_t* queue_alloc(int capacity);

queue_t* queue_copy(queue_t* queue);

void queue_free(queue_t** queue);

bool queue_empty(queue_t* queue);

int queue_size(queue_t* queue);

int queue_max_size(queue_t* queue);

bool queue_push_front(queue_t* queue, int value);

bool queue_push_back(queue_t* queue, int value);

int queue_pop_front(queue_t* queue);

int queue_pop_back(queue_t* queue);

/*
TODO:

resize
    Change size (public member function)

empty
    Test whether container is empty (public member function)

shrink_to_fit
    Shrink to fit (public member function)

at
    Access element (public member function)

front
    Access first element (public member function)

back
    Access last element (public member function)

insert
    Insert elements (public member function)

erase
    Erase elements (public member function)

clear
    Clear content (public member function)
*/
