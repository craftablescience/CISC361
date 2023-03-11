#pragma once

void swapi(int* x, int* y);

void sorti(int arr[], int n);

float avgi(const int arr[], int n);

#ifdef PRINT_INPUTS
    #define scanf scanf_printf
    int scanf_printf(const char* fmt, ...);
#endif
