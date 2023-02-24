#include <common.h>

#include <sum_time/singlethreaded/lib.h>
#include <sum_time/multithreaded/lib.h>

#define SMALL_SIZE 10000
#define LARGE_SIZE 100000000
#define SMALL_THREADS 2
#define LARGE_THREADS 8
#define NUM_ITERATIONS 5 // for more refined values

static void run_benchmark(long int size, int threads);

int main() {
    run_benchmark(SMALL_SIZE, SMALL_THREADS);
    run_benchmark(LARGE_SIZE, SMALL_THREADS);
    run_benchmark(SMALL_SIZE, LARGE_THREADS);
    run_benchmark(LARGE_SIZE, LARGE_THREADS);
}

static void run_benchmark(long int size, int threads) {
    int* arr = (int*) malloc(size * sizeof(int));
    printf("Size: %ld, Threads: 1... ", size);
    double time = 0.0;
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        time += compute_time_singlethreaded(arr, size, 0);
    }
    printf("%lf\n", time / NUM_ITERATIONS / CLOCKS_PER_SEC);

    printf("Size: %ld, Threads: %d... ", size, threads);
    time = 0.0;
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        time += compute_time_multithreaded(arr, size, threads, 0);
    }
    printf("%lf\n", time / NUM_ITERATIONS / CLOCKS_PER_SEC);
    free(arr);
}
