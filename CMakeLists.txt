cmake_minimum_required(VERSION 3.15)
project(CISC361 C)
set(CMAKE_C_STANDARD 11)

function(add_class_exercise name)
    set(SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/${name}/main.c")
    foreach(file IN LISTS ARGN)
        list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/${name}/${file}")
    endforeach()
    add_executable(${name} ${SOURCES})
endfunction()

add_class_exercise(hello_world)
