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
    int priority[MAX_PROCESSES];
    memset(arrival_time, 0, MAX_PROCESSES);
    memset(burst_time, 0, MAX_PROCESSES);
    memset(priority, 0, MAX_PROCESSES);

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
        do {
            printf("Priority (>= 0): ");
            scanf("%d", &priority[i]);
        } while (priority[i] < 0);
    }

    int quantum_time = 0;
    do {
        printf("\nEnter Time Quantum (>= 1): ");
        scanf("%d", &quantum_time);
    } while (quantum_time < 1);

    run_scheduler_round_robin_priority(num_processes, arrival_time, burst_time, priority, quantum_time);
}

#pragma clang diagnostic pop
