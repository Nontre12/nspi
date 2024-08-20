# NSPi (WIP)

[![Build package](https://github.com/Nontre12/nspi/actions/workflows/build.yml/badge.svg)](https://github.com/Nontre12/nspi/actions/workflows/build.yml)

**NSPi** is a work in progress Switch package downloader homebrew. Inspired by the PSVITA PKGi hombrew made by [@mmozeiko](https://github.com/mmozeiko) and PSP/PS3 ports by [@bucanero](https://github.com/bucanero).

The `nspi` homebrew app allows to download packages directly on your Switch

![](https://nontre.es/assets/2024-08-20-nspi.jpg)

## Build
To build this project from source, you'll need to set up the appropriate development environment.

### Requirements

- **devkitPro devkitA64 toolchain**: You can either install this toolchain directly on your system or use one of the available devkitPro Docker images.

### Option 1: Install devkitPro Toolchain

1. Follow the [devkitPro installation guide](https://devkitpro.org/wiki/Getting_Started) to set up the `devkitA64` toolchain on your system.
2. Ensure that the necessary tools (`nacptool`, `elf2nro`, etc.) are available in your PATH.

### Option 2: Use a devkitPro Docker Image

1. Pull one of the devkitPro Docker images that comes with all the precompiled tools and toolchains:
    ```bash
    docker pull devkitpro/devkita64
    ```

2. Use the Docker image to build the project
    ```bash
    docker run --rm -it -v "$(pwd):/app" --workdir=/app devkitpro/devkita64:latest bash
    cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain.cmake
    cd build
    make -j$(nproc)
    ```

### Note for libnx
In this project, instead of linking the precompiled libnx library provided by devkitPro, I preferred to add libnx compilation to the build process. This means that libnx will be built from source as part of this project's build process, ensuring that you have the latest version and any custom modifications needed for this project.

## Install
1. Download the `NSPi.nro` file.
2. Insert your SD card into your computer.
3. Copy the `NSPi.nro` file to the `switch/` folder on the root of your SD card.
4. Safely eject the SD card from your computer.
5. Insert the SD card back into your Nintendo Switch.

## License
This project is licensed under the GNU General Public License v3.0. See the [LICENSE](LICENSE) file for details.
