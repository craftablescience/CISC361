option(PRINT_INPUTS "Prints stdin input from custom scan function" OFF)

# Fixup names like "folder/bin" to "folder_bin"
macro(fixup_target_name NAME_RAW)
    # Path to targets
    set(NAME_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src/${NAME_RAW}")

    # Replace slashes and spaces
    string(REPLACE " " "_" NAME_BIN "${NAME_RAW}")
    string(REPLACE "\\" "_" NAME_BIN ${NAME_BIN})
    string(REPLACE "/"  "_" NAME_BIN ${NAME_BIN})

    # Remove underscore prefix
    string(FIND ${NAME_BIN} "_" NAME_FOUND_UNDERSCORE)
    if(NAME_FOUND_UNDERSCORE EQUAL 0)
        string(SUBSTRING ${NAME_BIN} 1 -1 NAME_BIN)
    endif()

    # Set library target name
    set(NAME_LIB ${NAME_BIN}_lib)
endmacro()

# Create the script file
set(GEN_OUTPUT_SCRIPT "${CMAKE_BINARY_DIR}/generate_output.sh")
file(WRITE ${GEN_OUTPUT_SCRIPT} "")
file(CHMOD ${GEN_OUTPUT_SCRIPT} PERMISSIONS OWNER_EXECUTE GROUP_EXECUTE WORLD_EXECUTE OWNER_READ GROUP_READ WORLD_READ)

# Add a new binary and/or library
function(add_class_exercise NAME_RAW)
    # Get optional dependencies
    cmake_parse_arguments(PARSE_ARGV 1 OPTIONS "" "" "DEPS;INPUTS;SOURCES;SOURCES_LIB")
    foreach(DEPENDENCY IN LISTS OPTIONS_DEPS)
        fixup_target_name(${DEPENDENCY})
        list(APPEND TGT_DEPENDENCIES ${NAME_LIB})
    endforeach()

    # Fix-up name for nested directories
    fixup_target_name(${NAME_RAW})

    # Add binary
    set(HAS_BIN OFF)
    if(EXISTS "${NAME_PATH}/main.c")
        set(HAS_BIN ON)
        message("-- Adding '${NAME_BIN}' binary")

        set(SOURCES_BIN "${NAME_PATH}/main.c")
        foreach(FILE IN LISTS OPTIONS_SOURCES)
            list(APPEND SOURCES "${NAME_PATH}/${FILE}")
        endforeach()
        add_executable(${NAME_BIN} ${SOURCES_BIN})

        list(APPEND GENERATED_TARGETS "${NAME_BIN}")

        if(OPTIONS_INPUTS)
            file(APPEND ${GEN_OUTPUT_SCRIPT} "echo \"\" > ./input.txt\n")
            foreach(INPUT IN LISTS OPTIONS_INPUTS)
                file(APPEND ${GEN_OUTPUT_SCRIPT} "echo \"${INPUT}\" >> ./input.txt\n")
            endforeach()
            file(APPEND ${GEN_OUTPUT_SCRIPT} "./${NAME_BIN} < ./input.txt > ${NAME_PATH}/output.txt\n")
        else()
            file(APPEND ${GEN_OUTPUT_SCRIPT} "./${NAME_BIN} > ${NAME_PATH}/output.txt\n")
        endif()
    endif()

    # Add library
    if(EXISTS "${NAME_PATH}/lib.c")
        message("-- Adding '${NAME_LIB}' library")

        list(APPEND SOURCES_LIB "${NAME_PATH}/lib.c" "${NAME_PATH}/lib.h")
        foreach(FILE IN LISTS OPTIONS_SOURCES_LIB)
            list(APPEND SOURCES_LIB "${NAME_PATH}/${FILE}")
        endforeach()
        add_library(${NAME_LIB} STATIC ${SOURCES_LIB})

        if(HAS_BIN)
            target_link_libraries(${NAME_BIN} PUBLIC ${NAME_LIB})
        endif()
        list(APPEND GENERATED_TARGETS "${NAME_LIB}")
    endif()

    # Add tests
    if(EXISTS "${NAME_PATH}/test.c")
        message("-- Adding '${NAME_LIB}' test")

        list(APPEND SOURCES_LIB_TEST "${NAME_PATH}/test.c")
        add_executable(${NAME_LIB}_test ${SOURCES_LIB_TEST})
        target_link_libraries(${NAME_LIB}_test PRIVATE ${NAME_LIB})

        list(APPEND GENERATED_TARGETS ${NAME_LIB}_test)

        file(APPEND ${GEN_OUTPUT_SCRIPT} "./${NAME_LIB}_test > ${NAME_PATH}/test_output.txt\n")
    endif()

    # Set include dir and link to pthread + rt
    foreach(TGT IN LISTS GENERATED_TARGETS)
        target_include_directories(${TGT} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
        target_link_libraries(${TGT} PUBLIC pthread rt ${TGT_DEPENDENCIES})
        if(NOT ${NAME_RAW} MATCHES "common")
            target_link_libraries(${TGT} PUBLIC common_lib)
        endif()
        if(PRINT_INPUTS)
            target_compile_definitions(${TGT} PUBLIC -DPRINT_INPUTS=1)
        endif()
    endforeach()
endfunction()

# Common utils library
add_class_exercise(_common SOURCES_LIB queue.h queue.c)

# Add a new binary and/or library in the homework folder
macro(add_homework_exercise NAME_RAW)
    add_class_exercise("_homework/${NAME_RAW}")
endmacro()
