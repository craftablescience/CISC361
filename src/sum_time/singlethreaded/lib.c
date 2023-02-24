#include <common.h>

double compute_time_singlethreaded(int* arr, long int arrLen, int enablePrinting) {
    long long int sum = 0;
    long long int* pSum = &sum; // to be at least somewhat consistent with multithreaded

    for (int i = 0; i < arrLen; i++) {
        arr[i] = i + 1;
    }

    // Setup timing
    clock_t start, end;
    double cpu_time_taken;
    start = clock();

    // Summing code here
    for (int i = 0; i < arrLen; i++) {
        *pSum += arr[i];
    }

    // Time calculations here
    end = clock();
    cpu_time_taken = (double)(end - start);

    if (enablePrinting) {
        printf("Total sum: %lld\n", sum);
        printf("Time taken to sum all the numbers is %lf seconds\n", cpu_time_taken / CLOCKS_PER_SEC);
    }

    return cpu_time_taken;
}
