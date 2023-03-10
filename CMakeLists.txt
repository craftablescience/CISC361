cmake_minimum_required(VERSION 3.19)
project(CISC361 C)
set(CMAKE_C_STANDARD 11)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake_scripts")
include(ExerciseRegistration)

# Exercises from 1
add_class_exercise(fork)
add_class_exercise(hello_world)
add_class_exercise(sum_time/singlethreaded)
add_class_exercise(sum_time/multithreaded)
add_class_exercise(sum_time/time_analysis DEPS sum_time/singlethreaded sum_time/multithreaded)


# Exercises from 2
add_class_exercise(scheduling)
add_class_exercise(scheduling/fcfs                 DEPS scheduling INPUTS 3 0 10 2 20 3 5)
add_class_exercise(scheduling/round_robin          DEPS scheduling INPUTS 3 0 10 2 20 3 5 5)
add_class_exercise(scheduling/fcfs_priority        DEPS scheduling INPUTS 3 0 10 1 2 20 2 3 5 2)
add_class_exercise(scheduling/round_robin_priority DEPS scheduling INPUTS 3 0 10 1 2 20 2 3 5 2 5)


# Homework implementations
add_homework_exercise(fork_global_copied)
add_homework_exercise(fork_pthread)
