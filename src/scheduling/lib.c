#include "lib.h"

#include <common.h>

static void run_scheduler(bool use_round_robin, int num_processes, int arrival_time[], int burst_time[], int quantum_time);

void run_scheduler_fcfs(int num_processes, int arrival_time[], int burst_time[]) {
    run_scheduler(false, num_processes, arrival_time, burst_time, 0);
}

void run_scheduler_round_robin(int num_processes, int arrival_time[], int burst_time[], int quantum_time) {
    run_scheduler(true, num_processes, arrival_time, burst_time, quantum_time);
}

void run_scheduler_fcfs_priority(int num_processes, int arrival_time[], int burst_time[], int priority[]) {
    // todo: fcfs priority
}

void run_scheduler_round_robin_priority(int num_processes, int arrival_time[], int burst_time[], int priority[], int quantum_time) {
    // todo: round robin priority
}

static void run_scheduler(bool use_round_robin, int num_processes, int arrival_time[], int burst_time[], int quantum_time) {
    int wait_times[MAX_PROCESSES];
    int turnaround_times[MAX_PROCESSES];

    // Perform Scheduling Calculations
    printf("\nProcess ID\tArrival Time\tBurst Time\tTurnaround Time\tWaiting Time\n");
    if (!use_round_robin) {
        // Sorts the processes based on their arrival time
        // bubble sort ftw
        for (int i = 0; i < num_processes - 1; i++) {
            for (int j = 0; j < num_processes - i - 1; j++) {
                if (arrival_time[j] > arrival_time[j + 1]) {
                    swap(&arrival_time[j], &arrival_time[j + 1]);
                    swap(&burst_time[j], &burst_time[j + 1]);
                }
            }
        }

        // Calculates their waiting and turnaround times in the order they arrived
        int wait_time = 0;
        for (int i = 0; i < num_processes; wait_time += burst_time[i], i++) {
            int current_wait_time = wait_time - arrival_time[i];
            int turnaround_time = burst_time[i] + current_wait_time;
            printf("Process #%d\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, arrival_time[i], burst_time[i], turnaround_time, current_wait_time);
            wait_times[i] = current_wait_time;
            turnaround_times[i] = turnaround_time;
        }
    } else {
        // todo: round robin
    }

    // Print Average Wait and Turnaround Times
    printf("\n\nAverage Waiting Time: %f", avg(wait_times, num_processes));
    printf("\nAverage Turnaround Time: %f\n", avg(turnaround_times, num_processes));
}
