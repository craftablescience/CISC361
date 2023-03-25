#include "lib.h"

#include <common.h>

static void run_scheduler(bool use_round_robin, bool use_priority, int num_processes, int arrival_time[], int burst_time[], int priority[], int quantum_time);

void run_scheduler_fcfs(int num_processes, int arrival_time[], int burst_time[]) {
    run_scheduler(false, false, num_processes, arrival_time, burst_time, NULL, 0);
}

void run_scheduler_round_robin(int num_processes, int arrival_time[], int burst_time[], int quantum_time) {
    run_scheduler(true, false, num_processes, arrival_time, burst_time, NULL, quantum_time);
}

void run_scheduler_fcfs_priority(int num_processes, int arrival_time[], int burst_time[], int priority[]) {
    run_scheduler(false, true, num_processes, arrival_time, burst_time, priority, 0);
}

void run_scheduler_round_robin_priority(int num_processes, int arrival_time[], int burst_time[], int priority[], int quantum_time) {
    run_scheduler(true, true, num_processes, arrival_time, burst_time, priority, quantum_time);
}

static void run_scheduler(bool use_round_robin, bool use_priority, int num_processes, int arrival_time[], int burst_time[], int priority[], int quantum_time) {
    int wait_times[MAX_PROCESSES];
    int turnaround_times[MAX_PROCESSES];

    // Perform Scheduling Calculations
    printf("\nProcess ID\tArrival Time\tBurst Time\tTurnaround Time\tWaiting Time\n");

    int wait_time = 0;
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
        for (int i = 0; i < num_processes; wait_time += burst_time[i], i++) {
            wait_times[i] = wait_time - arrival_time[i];
            turnaround_times[i] = wait_time - arrival_time[i] + burst_time[i];
            printf("Process #%d\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, arrival_time[i], burst_time[i], turnaround_times[i], wait_times[i]);
        }
    } else {
        // Round-robin doesn't go through each process in one go
        int remaining_time[MAX_PROCESSES];
        memcpy(remaining_time, burst_time, MAX_PROCESSES * sizeof(int));

        queue_t* process_queue = queue_alloc(num_processes);

        int i = 0; // The number of processed processes
        int process = -1; // The current process (<0 being invalid)

        // I love Rust 🥰🥰🥰
        loop {
            // If we have new arrivals, add them to the queue
            while (i < num_processes && arrival_time[i] <= wait_time && i != process) {
                queue_push_back(process_queue, i);
                ++i;
            }
            // If we had a process on an earlier loop and its not done, add it to the end
            if (process != -1 && remaining_time[process] > 0) {
                queue_push_back(process_queue, process);
            }

            // If the queue is empty and we processed every process we are done
            if (queue_empty(process_queue) && i == num_processes) {
                break;
            }

            // New current process from the queue
            process = queue_pop_front(process_queue);

            // If the process is less than the quantum, finish it, otherwise subtract the quantum from its remaining time
            if (remaining_time[process] <= quantum_time) {
                wait_time += remaining_time[process];
                remaining_time[process] = 0;

                wait_times[process] = wait_time - arrival_time[process] - burst_time[process];
                turnaround_times[process] = wait_time - arrival_time[process];

                printf("Process #%d\t%d\t\t%d\t\t%d\t\t%d\n", process + 1, arrival_time[process], burst_time[process], turnaround_times[process], wait_times[process]);
            } else {
                wait_time += quantum_time;
                remaining_time[process] -= quantum_time;
            }
        }

        // Pretty important
        queue_free(&process_queue);
    }

    // Print average wait and turnaround times
    printf("\n\nAverage Waiting Time: %f", avg(wait_times, num_processes));
    printf("\nAverage Turnaround Time: %f\n", avg(turnaround_times, num_processes));
}
