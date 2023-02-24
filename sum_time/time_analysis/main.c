#include <common.h>

#include "../singlethreaded/lib.h"
#include "../multithreaded/lib.h"

#define NUM_TRIALS     5
#define NUM_ITERATIONS 10

int main() {
    for (int t = 0; t < NUM_TRIALS; t++) {
        printf("Trial %d/%d\n", t + 1, NUM_TRIALS);

        printf("- Running %d singlethreaded additions... ", NUM_ITERATIONS);
        double time = 0.0;
        for (int i = 0; i < NUM_ITERATIONS; i++) {
            time += compute_time_singlethreaded(0);
        }
        printf("%lf\n", time / CLOCKS_PER_SEC);

        printf("- Running %d multithreaded additions...  ", NUM_ITERATIONS);
        time = 0.0;
        for (int i = 0; i < NUM_ITERATIONS; i++) {
            time += compute_time_multithreaded(0);
        }
        printf("%lf\n", time / CLOCKS_PER_SEC);
    }
}
