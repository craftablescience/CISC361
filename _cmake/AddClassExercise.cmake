function(add_class_exercise NAME_RAW)
    # Get optional dependencies
    cmake_parse_arguments(PARSE_ARGV 1 OPTIONS "" "" "DEPS;SOURCES;SOURCES_LIB")

    # Fix-up name for nested directories
    string(REPLACE "\\" "_" NAME_BIN "${NAME_RAW}")
    string(REPLACE "/"  "_" NAME_BIN "${NAME_BIN}")
    set(NAME_LIB "${NAME_BIN}_lib")
    set(NAME_PATH "${CMAKE_CURRENT_SOURCE_DIR}/${NAME_RAW}")

    # Add binary
    message("- Adding '${NAME_BIN}' binary")
    set(SOURCES_BIN "${NAME_PATH}/main.c")
    foreach(FILE IN LISTS OPTIONS_SOURCES)
        list(APPEND SOURCES "${NAME_PATH}/${FILE}")
    endforeach()
    add_executable(${NAME_BIN} ${SOURCES_BIN})
    list(APPEND GENERATED_TARGETS "${NAME_BIN}")

    # Add library
    if(EXISTS "${NAME_PATH}/lib.c")
        message("- Adding '${NAME_LIB}' library")
        list(APPEND SOURCES_LIB "${NAME_PATH}/lib.c" "${NAME_PATH}/lib.h")
        foreach(FILE IN LISTS OPTIONS_SOURCES_LIB)
            list(APPEND SOURCES_LIB "${NAME_PATH}/${FILE}")
        endforeach()
        add_library(${NAME_LIB} ${SOURCES_LIB})
        target_link_libraries(${NAME_BIN} PUBLIC ${NAME_LIB})
        list(APPEND GENERATED_TARGETS "${NAME_LIB}")
    endif()

    # Set include dir and link to pthread
    foreach(TGT IN LISTS GENERATED_TARGETS)
        target_include_directories(${TGT} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/_common/")
        target_link_libraries(${TGT} PUBLIC pthread ${OPTIONS_DEPS})
    endforeach()
endfunction()
