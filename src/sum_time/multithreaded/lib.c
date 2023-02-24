#include "lib.h"

#include <common.h>

#define MAX_THREAD_COUNT 8

typedef struct {
    long long int* sum;
    pthread_t thread_id;
    int thread_number;
    int* arr;
    long int start;
    long int end;
} arg_data;

static void* worker_sum(void* arg) {
    arg_data* current_thread_data = (arg_data*) arg;

    long long int current_sum = 0;
    for (long int i = current_thread_data->start; i < current_thread_data->end; i++) {
        current_sum += current_thread_data->arr[i];
    }
    *(current_thread_data->sum) += current_sum;

    return NULL;
}

double compute_time_multithreaded(int* arr, long int arrLen, int threadCount, int enablePrinting) {
    long long int sum = 0;

    if (threadCount > MAX_THREAD_COUNT) {
        threadCount = MAX_THREAD_COUNT;
    }

    // Let the array consists of first MAX_NO_OF_ELEMENTS integers,
    // 1 to MAX_NO_OF_ELEMENTS
    for (int i = 0; i < arrLen; i++) {
        arr[i] = i + 1;
    }

    // Argument data to send in worker functions
    arg_data thread_data[MAX_THREAD_COUNT];

    // Total number of threads we will create
    if (enablePrinting) {
        printf("Creating %d number of threads...\n", threadCount);
    }

    // Setup timing
    clock_t start, end;
    double cpu_time_taken;
    start = clock();

    // Creating the child threads
    for (int i = 0; i < threadCount; i++) {
        thread_data[i].sum = &sum;
        thread_data[i].thread_number = i + 1;
        thread_data[i].arr = arr;
        thread_data[i].start = i * (arrLen / threadCount);
        thread_data[i].end = thread_data[i].start + (arrLen / threadCount);
        if (thread_data[i].end > arrLen) {
            thread_data[i].end = arrLen;
        }
        pthread_create(&thread_data[i].thread_id, NULL, &worker_sum, &thread_data[i]);
    }

    // Joining the threads one by one
    for (int i = 0; i < threadCount; i++) {
        void* result = NULL;
        pthread_join(thread_data[i].thread_id, &result);
    }
    end = clock();
    cpu_time_taken = (double)(end - start);

    if (enablePrinting) {
        printf("Total sum: %lld\n", sum);
        printf("Time taken to sum all the numbers: %lf\n", cpu_time_taken / CLOCKS_PER_SEC);
    }

    return cpu_time_taken;
}
