#include <prelude.h>

#define MAX_NO_OF_ELEMENTS 100000000

long long int sum;
int arr[MAX_NO_OF_ELEMENTS];

int main() {
    // Let the array consists of first MAX_NO_OF_ELEMENTS integers,
    // 1 to MAX_NO_OF_ELEMENTS
    for (int i = 0; i < MAX_NO_OF_ELEMENTS; i++) {
        arr[i] = i + 1;
    }

    // Setup timing
    clock_t start, end;
    double cpu_time_taken;
    start = clock();

    // Summing code here
    for (int i = 0; i < MAX_NO_OF_ELEMENTS; i++) {
        sum += arr[i];
    }

    // Time calculations here
    end = clock();
    cpu_time_taken = end - start;

    printf("Total sum: %lld\n", sum);
    printf("Time taken to sum all the numbers is %lf seconds\n", cpu_time_taken / CLOCKS_PER_SEC);

    return 0;
}
