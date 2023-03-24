#pragma once

#include "queue.h"

// I love Rust 🥰🥰🥰
#define loop for(;;)

void swap(int* x, int* y);

void sort(int arr[], int n);

float avg(const int arr[], int n);

#ifdef PRINT_INPUTS
    #define scanf scanf_printf
    int scanf_printf(const char* fmt, ...);
#endif
