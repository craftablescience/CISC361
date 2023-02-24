#include "lib.h"

#define ARRAY_SIZE 100000000

int arr[ARRAY_SIZE];

int main() {
    compute_time_singlethreaded(arr, ARRAY_SIZE, 1);
    return 0;
}
