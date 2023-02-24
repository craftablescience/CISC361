#include "lib.h"

#define ARRAY_SIZE  100000000
#define NUM_THREADS 4

int arr[ARRAY_SIZE];

int main() {
    compute_time_multithreaded(arr, ARRAY_SIZE, NUM_THREADS, 1);
    return 0;
}
