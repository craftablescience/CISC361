#include <common.h>

void swapi(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void sorti(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swapi(&arr[j], &arr[j + 1]);
            }
        }
    }
}

float avgi(const int arr[], int n) {
    float sum = 0.f;
    for (int i = 0; i < n; i++) {
        sum += (float) arr[i];
    }
    return sum / (float) n;
}
