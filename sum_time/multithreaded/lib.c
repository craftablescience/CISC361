#include "lib.h"

#include <common.h>

#define MAX_NO_OF_ELEMENTS 100000000
#define MAX_NO_OF_THREADS 4

long long int sum_m;
int arr_m[MAX_NO_OF_ELEMENTS];

typedef struct {
    pthread_t thread_id;
    int thread_number;
    int start;
    int end;
} arg_data;

static void* worker_sum(void* arg) {
    arg_data* current_thread_data = (arg_data*) arg;

    long long int current_sum = 0;
    for (int i = current_thread_data->start; i < current_thread_data->end; i++) {
        current_sum += arr_m[i];
    }
    sum_m += current_sum;

    return NULL;
}

double compute_time_multithreaded(int enablePrinting) {
    // Let the array consists of first MAX_NO_OF_ELEMENTS integers,
    // 1 to MAX_NO_OF_ELEMENTS
    for (int i = 0; i < MAX_NO_OF_ELEMENTS; i++) {
        arr_m[i] = i + 1;
    }

    // Argument data to send in worker functions
    arg_data thread_data[MAX_NO_OF_THREADS];

    // Total number of threads we will create
    if (enablePrinting) {
        printf("Creating %d number of threads...\n", MAX_NO_OF_THREADS);
    }

    // Setup timing
    clock_t start, end;
    double cpu_time_taken;
    start = clock();

    // Creating the child threads
    for (int i = 0; i < MAX_NO_OF_THREADS; i++) {
        thread_data[i].thread_number = i + 1;
        thread_data[i].start = i * (MAX_NO_OF_ELEMENTS / MAX_NO_OF_THREADS);
        thread_data[i].end = thread_data[i].start + (MAX_NO_OF_ELEMENTS / MAX_NO_OF_THREADS);
        if (thread_data[i].end > MAX_NO_OF_ELEMENTS) {
            thread_data[i].end = MAX_NO_OF_ELEMENTS;
        }
        pthread_create(&thread_data[i].thread_id, NULL, &worker_sum, &thread_data[i]);
    }

    // Joining the threads one by one
    for (int i = 0; i < MAX_NO_OF_THREADS; i++) {
        void* result = NULL;
        pthread_join(thread_data[i].thread_id, &result);
    }
    end = clock();
    cpu_time_taken = (double)(end - start);

    if (enablePrinting) {
        printf("Total sum: %lld\n", sum_m);
        printf("Time taken to sum all the numbers: %lf\n", cpu_time_taken / CLOCKS_PER_SEC);
    }

    return cpu_time_taken;
}
