cmake_minimum_required(VERSION 3.15)
project(CISC361 C)
set(CMAKE_C_STANDARD 11)

function(add_class_exercise name)
    # Add sources
    set(SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/${name}/main.c")
    foreach(file IN LISTS ARGN)
        list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/${name}/${file}")
    endforeach()

    # Fix-up name for nested directories
    string(REPLACE "\\" "_" name "${name}")
    string(REPLACE "/"  "_" name "${name}")

    # Add target
    add_executable(${name} ${SOURCES})
    target_include_directories(${name} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/_common/")
    target_link_libraries(${name} PUBLIC pthread)
endfunction()

add_class_exercise(hello_world)
add_class_exercise(fork)
add_class_exercise(sum_time/singlethreaded)
add_class_exercise(sum_time/multithreaded)
