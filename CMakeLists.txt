cmake_minimum_required(VERSION 3.15)
project(CISC361 C)
set(CMAKE_C_STANDARD 11)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake_scripts")
include(AddClassExercise)

# Exercises
add_class_exercise(fork)
add_class_exercise(hello_world)
add_class_exercise(sum_time/singlethreaded)
add_class_exercise(sum_time/multithreaded)
add_class_exercise(sum_time/time_analysis DEPS sum_time/singlethreaded sum_time/multithreaded)

# Homework implementations
add_homework_exercise(fork_global_copied)
