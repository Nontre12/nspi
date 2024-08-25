set(CMAKE_SYSTEM_NAME Switch)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

set(CMAKE_C_COMPILER_TARGET aarch64-none-elf)
set(CMAKE_CXX_COMPILER_TARGET aarch64-none-elf)

set(CMAKE_C_COMPILER /opt/devkitpro/devkitA64/bin/aarch64-none-elf-gcc)
set(CMAKE_CXX_COMPILER /opt/devkitpro/devkitA64/bin/aarch64-none-elf-g++)
# NOTE: Assembly is being compiled with gcc
set(CMAKE_ASM_COMPILER /opt/devkitpro/devkitA64/bin/aarch64-none-elf-gcc)

set(CMAKE_AR /opt/devkitpro/devkitA64/bin/aarch64-none-elf-ar)
set(CMAKE_LD /opt/devkitpro/devkitA64/bin/aarch64-none-elf-ld)
set(CMAKE_NM /opt/devkitpro/devkitA64/bin/aarch64-none-elf-nm)
set(CMAKE_OBJCOPY /opt/devkitpro/devkitA64/bin/aarch64-none-elf-objcopy)
set(CMAKE_OBJDUMP /opt/devkitpro/devkitA64/bin/aarch64-none-elf-objdump)
set(CMAKE_RANLIB /opt/devkitpro/devkitA64/bin/aarch64-none-elf-ranlib)
set(CMAKE_STRIP /opt/devkitpro/devkitA64/bin/aarch64-none-elf-strip)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=armv8-a+crc+crypto -mtune=cortex-a57 -mtp=soft")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=armv8-a+crc+crypto -mtune=cortex-a57 -mtp=soft")
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -march=armv8-a+crc+crypto -mtune=cortex-a57 -mtp=soft")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -march=armv8-a+crc+crypto -mtune=cortex-a57 -mtp=soft")