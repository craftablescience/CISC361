#pragma once

#define MAX_PROCESSES 16

void run_scheduler_fcfs(int num_processes, int arrival_time[], int burst_time[]);
void run_scheduler_round_robin(int num_processes, int arrival_time[], int burst_time[], int quantum_time);

void run_scheduler_fcfs_priority(int num_processes, int arrival_time[], int burst_time[], int priority[]);
void run_scheduler_round_robin_priority(int num_processes, int arrival_time[], int burst_time[], int priority[], int quantum_time);
