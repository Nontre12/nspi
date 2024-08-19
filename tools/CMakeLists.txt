cmake_minimum_required(VERSION 3.18)
project(switch_tools VERSION 1.12.0 LANGUAGES C)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SWITCH_TOOLS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/switch-tools/src)

# elf2nro
add_executable(elf2nro
    ${SWITCH_TOOLS_PATH}/elf2nro.c
    ${SWITCH_TOOLS_PATH}/romfs.c
    ${SWITCH_TOOLS_PATH}/filepath.c
)

target_include_directories(elf2nro PRIVATE ${SWITCH_TOOLS_PATH} /usr/include)

target_link_libraries(elf2nro PRIVATE /usr/lib/x86_64-linux-gnu/liblz4.a)

# nacptool
add_executable(nacptool ${SWITCH_TOOLS_PATH}/nacptool.c)

target_include_directories(elf2nro PRIVATE ${SWITCH_TOOLS_PATH})
