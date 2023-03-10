#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"

#include <common.h>

#include <scheduling/lib.h>

int main() {
    // Define Number of Processes
    int num_processes = 0;
    do {
        printf("Enter Total Number of Processes (1-%d inclusive): ", MAX_PROCESSES);
        scanf("%d", &num_processes);
    } while (num_processes < 1 || num_processes > 16);

    // Define Process Details
    int arrival_time[MAX_PROCESSES];
    int burst_time[MAX_PROCESSES];
    memset(arrival_time, 0, MAX_PROCESSES);
    memset(burst_time, 0, MAX_PROCESSES);

    for (int i = 0; i < num_processes; i++) {
        printf("Enter Details of Process #%d...\n", i + 1);
        do {
            printf("Arrival Time (>= 0): ");
            scanf("%d", &arrival_time[i]);
        } while (arrival_time[i] < 0);
        do {
            printf("Burst Time (> 0): ");
            scanf("%d", &burst_time[i]);
        } while (burst_time[i] <= 0);
    }

    run_scheduler_fcfs(num_processes, arrival_time, burst_time);
}

#pragma clang diagnostic pop
