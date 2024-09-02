cmake_minimum_required(VERSION 3.10)

# Project name and version
project(NSPi VERSION 0.0.4 LANGUAGES C CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra")
set(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -Wall -Wextra")

set(BUILD_SHARED_LIBS OFF)

set(APP_AUTHOR_NAME "Nontre")
set(APP_NAME "NSPi")
set(APP_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})

set(SWITCH_BUILD OFF)
set(ELF_APP ${APP_NAME})

if (CMAKE_SYSTEM_NAME MATCHES "Switch")
set(SWITCH_BUILD ON)
set(ELF_APP ${APP_NAME}.elf)
endif()

configure_file(nspi_config.h.in ${CMAKE_CURRENT_BINARY_DIR}/nspi_config.h @ONLY)

# Define the target and its sources
set(SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/nspi_console.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/nspi_pad.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/nspi_menu.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/nspi_menu_manager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/nspi_title_selector_menu.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/nspi_title_menu.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/nspi_app.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/nspi_logger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/nspi_logger_menu.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/nspi_selectable_menu.cpp
)

add_executable(${ELF_APP} ${SOURCE_FILES})

# Include directories
target_include_directories(${ELF_APP} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}
)

if (SWITCH_BUILD)
target_include_directories(${ELF_APP} PRIVATE /opt/devkitpro/portlibs/switch/include)
endif()

# Compilation flags
target_compile_options(${ELF_APP} PRIVATE
    -ffunction-sections
    -fPIE
    -fno-exceptions
    -DCURL_STATICLIB # curl-config --cflags
)

if (SWITCH_BUILD)
# Linker flags
target_link_options(${ELF_APP} PRIVATE
    -specs=${CMAKE_CURRENT_SOURCE_DIR}/lib/libnx/nx/switch.specs
    -fPIE
    -Wl,-Map,${CMAKE_CURRENT_BINARY_DIR}/${APP_NAME}.map
)
endif()

add_subdirectory(lib)

if (SWITCH_BUILD)
target_link_directories(${ELF_APP} PRIVATE /opt/devkitpro/portlibs/switch/lib)
endif()

if (SWITCH_BUILD)
target_link_libraries(${ELF_APP} PRIVATE nlohmann_json curl z nx)
else()
target_link_libraries(${ELF_APP} PRIVATE nlohmann_json curl z)
endif()

# Post-build steps
if (SWITCH_BUILD)
# Create LST file
add_custom_command(TARGET ${ELF_APP} POST_BUILD
    COMMAND ${CMAKE_NM} -CSn $<TARGET_FILE:${ELF_APP}> > ${APP_NAME}.lst
    COMMENT "Creating LST symbols file from ELF (debug purposes)"
)

# Create NACP file
add_custom_command(TARGET ${ELF_APP} POST_BUILD
    COMMAND nacptool --create ${APP_NAME} ${APP_AUTHOR_NAME} ${APP_VERSION} ${CMAKE_CURRENT_BINARY_DIR}/${APP_NAME}.nacp
    COMMENT "Creating NACP file"
)

# Convert ELF to NRO
add_custom_command(TARGET ${ELF_APP} POST_BUILD
    COMMAND elf2nro $<TARGET_FILE:${ELF_APP}>
                    ${CMAKE_CURRENT_BINARY_DIR}/${APP_NAME}.nro
                    --nacp=${CMAKE_CURRENT_BINARY_DIR}/${APP_NAME}.nacp
                    --icon=${CMAKE_CURRENT_SOURCE_DIR}/icon.jpg
            ${CMAKE_CURRENT_BINARY_DIR}/${APP_NAME}.nro
            ${CMAKE_CURRENT_BINARY_DIR}/${APP_NAME}.nacp
            ${CMAKE_CURRENT_SOURCE_DIR}/icon.jpg
    COMMENT "Converting ELF to NRO"
)
endif()
