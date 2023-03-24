#include <common.h>

void swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

float avg(const int arr[], int n) {
    float sum = 0.f;
    for (int i = 0; i < n; i++) {
        sum += (float) arr[i];
    }
    return sum / (float) n;
}

#ifdef PRINT_INPUTS
int scanf_printf(const char* fmt, ...) {
    int ret;
    char in[1024];
    fgets(in, sizeof(in), stdin);

    va_list args;
    va_start(args, fmt);
    ret = vsscanf(in, fmt, args);
    vprintf(in, args);
    va_end(args);

    return ret;
}
#endif
