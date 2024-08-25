cmake_minimum_required(VERSION 3.18)
project(nx VERSION 4.7.0 LANGUAGES ASM C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(LIBNX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/libnx/nx)

# Path for the generated header file and temporary assembly file
set(TMP_ASM_FILE ${CMAKE_CURRENT_BINARY_DIR}/default_font.bin.s)
set(BINARY_FILE ${LIBNX_PATH}/data/default_font.bin)

# Custom command to generate the header file from default_font.bin
add_custom_command(
    OUTPUT ${TMP_ASM_FILE}
    COMMAND ${CMAKE_COMMAND} -E env bin2s -a 8 -H default_font_bin.h ${BINARY_FILE} > ${TMP_ASM_FILE}
    DEPENDS ${BINARY_FILE}
    COMMENT "Generating header file default_font_bin.h from default_font.bin"
    VERBATIM
)

# Create a custom target to ensure the custom commands run before compilation
add_custom_target(generate_default_font_header ALL
    DEPENDS ${TMP_ASM_FILE}
)

# Collect source files
file(GLOB_RECURSE SOURCE_FILES
    ${LIBNX_PATH}/source/*.c
    ${LIBNX_PATH}/source/*.cpp
    ${LIBNX_PATH}/source/*.s
)

# Create the library
add_library(nx ${SOURCE_FILES} ${TMP_ASM_FILE})

add_dependencies(nx generate_default_font_header)

# Include directories
target_include_directories(nx PUBLIC
    ${LIBNX_PATH}/include
    ${LIBNX_PATH}/external/bsd/include
    ${CMAKE_CURRENT_BINARY_DIR}
)

# Compile options
target_compile_options(nx PRIVATE
    -ffunction-sections
    -fdata-sections
    -mtp=soft
    -fPIC
    -ftls-model=local-exec
    -iquote ${LIBNX_PATH}/include/switch/
    -D__SWITCH__
    -DLIBNX_NO_DEPRECATION
)

# Apply custom flags to assembly files (*.s)
file(GLOB_RECURSE ASM_FILES ${LIBNX_PATH}/source/*.s
                            # Workarround for default_font.bin.s
                            ${TMP_ASM_FILE}
)

# Set custom flags for assembly files
set_source_files_properties(${ASM_FILES} PROPERTIES COMPILE_FLAGS
    "-x assembler-with-cpp -mtp=soft -fPIC -ftls-model=local-exec"
)
