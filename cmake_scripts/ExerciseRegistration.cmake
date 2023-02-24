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

# Add a new binary and/or library
function(add_class_exercise NAME_RAW)
    # Get optional dependencies
    cmake_parse_arguments(PARSE_ARGV 1 OPTIONS "" "" "DEPS;SOURCES;SOURCES_LIB")
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

        file(APPEND ${GEN_OUTPUT_SCRIPT} "./${NAME_BIN} > ${NAME_PATH}/output.txt\n")
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

    # Set include dir and link to pthread
    foreach(TGT IN LISTS GENERATED_TARGETS)
        target_include_directories(${TGT} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
        target_link_libraries(${TGT} PUBLIC pthread ${TGT_DEPENDENCIES})
        if(NOT ${NAME_RAW} MATCHES "common")
            target_link_libraries(${TGT} PUBLIC common_lib)
        endif()
    endforeach()
endfunction()

# Common utils library - must be ran before any other calls to this function!
add_class_exercise(_common)

# Add a new binary and/or library in the homework folder
macro(add_homework_exercise NAME_RAW)
    add_class_exercise("_homework/${NAME_RAW}")
endmacro()