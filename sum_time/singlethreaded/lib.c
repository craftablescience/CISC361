#include <common.h>

#define MAX_NO_OF_ELEMENTS 100000000

long long int sum_s = 0;
int arr_s[MAX_NO_OF_ELEMENTS];

double compute_time_singlethreaded(int enablePrinting) {
    // Let the array consists of first MAX_NO_OF_ELEMENTS integers,
    // 1 to MAX_NO_OF_ELEMENTS
    for (int i = 0; i < MAX_NO_OF_ELEMENTS; i++) {
        arr_s[i] = i + 1;
    }

    // Setup timing
    clock_t start, end;
    double cpu_time_taken;
    start = clock();

    // Summing code here
    for (int i = 0; i < MAX_NO_OF_ELEMENTS; i++) {
        sum_s += arr_s[i];
    }

    // Time calculations here
    end = clock();
    cpu_time_taken = (double)(end - start);

    if (enablePrinting) {
        printf("Total sum: %lld\n", sum_s);
        printf("Time taken to sum all the numbers is %lf seconds\n", cpu_time_taken / CLOCKS_PER_SEC);
    }

    return cpu_time_taken;
}
