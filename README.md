# NSPi (WIP)

[![GitHub Build Package](https://github.com/Nontre12/nspi/actions/workflows/build.yml/badge.svg)](https://github.com/Nontre12/nspi/actions/workflows/build.yml)
![GitHub Release](https://img.shields.io/github/v/release/Nontre12/nspi?include_prereleases)
[![GitHub License](https://img.shields.io/github/license/Nontre12/nspi)](LICENSE)

**NSPi** is a work in progress Switch package downloader homebrew. Inspired by the PSVITA PKGi hombrew made by [@mmozeiko](https://github.com/mmozeiko) and PSP/PS3 ports by [@bucanero](https://github.com/bucanero).

The `nspi` homebrew app allows to download packages directly on your Switch

![](https://nontre.es/assets/2024-08-20-nspi.jpg)

## Features
At this point in development, NSPi is **only capable of obtaining a massive listing of titles from a remote archive** generated via @blawar's [titledb](https://github.com/blawar/titledb) tool and providing a basic interface for browsing the listing.

## Install
1. Download the `NSPi.nro` file.
2. Insert your SD card into your computer.
3. Copy the `NSPi.nro` file to the `switch/` folder on the root of your SD card.
4. Safely eject the SD card from your computer.
5. Insert the SD card back into your Nintendo Switch.

## Usage
**ALWAYS RUN IN APPLICATION MODE**

### Controls
#### Movement
- `<` Fast up
- `>` Fast down
- `^` Up
- `v` Down
#### Actions
- `-` Load remote file with available titles. **NOTE THAT THIS WILL TAKE SEVERAL SECONDS TO LOAD.**
- `+` Exit from homebrew.
- `X` De/Select entries.
- `B` Return to last menu.
- `A` Browse basic title info.
- `Y` Show hombrew logs.

## Development

### Build (Switch)
To build this project from source, you'll need to set up the appropriate development environment.

#### Requirements

- devkitPro devkitA64 toolchain
- switch-curl
- switch-libz

#### Option 1: Install devkitPro Toolchain

1. Follow the [devkitPro installation guide](https://devkitpro.org/wiki/Getting_Started) to set up the `devkitA64` toolchain on your system.
2. Ensure that the necessary tools (`nacptool`, `elf2nro`, etc.) are available in your PATH.

#### Option 2: Use a devkitPro Docker Image

1. Pull one of the devkitPro Docker images that comes with all the precompiled tools and toolchains:
    ```bash
    docker pull devkitpro/devkita64
    ```

2. Use the Docker image to build the project
    ```bash
    docker run --rm -it -v "$(pwd):/app" --workdir=/app devkitpro/devkita64:latest bash
    cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain.cmake -DCMAKE_BUILD_TYPE=Release
    cd build
    make -j$(nproc)
    ```

3. Send built package to switch with nxlink (optional)
    ```bash
    nxlink -a xxx.xxx.xxx.xxx NSPi.nro
    ```

### Debug (nxlink)

0. [optional] **NOTE:** If using docker for building and debugging, you should run container with `--network=host`,
or at least make NXLINK ports accessible.

    ```cxx
    // nxlink.h

    #define NXLINK_SERVER_PORT 28280 ///< nxlink TCP server port
    #define NXLINK_CLIENT_PORT 28771 ///< nxlink TCP client port
    ```
    Start docker container `docker run --rm -it -v "$(pwd):/app" --network=host --workdir=/app devkitpro/devkita64:latest bash`

1. Build with `-DCMAKE_BUILD_TYPE=Debug` flag
2. Start nxlink server:
    ```bash
    nxlink -s -a xxx.xxx.xxx.xxx NSPi.nro
    ```
3. Then you should start seeing logger output on nxlink server
    ```bash
    # nxlink -s -a 192.168.0.142 NSPi.nro
    Sending NSPi.nro, 5834949 bytes
    2082853 sent (35.70%), 174 blocks
    starting server
    server active ...
    [DEBUG] Successfully established connection with nxlink server
    [DEBUG] Started App::mainLoop()
    ```

### Note for libnx
In this project, instead of linking the precompiled libnx library provided by devkitPro, I preferred to add libnx compilation to the build process. This means that libnx will be built from source as part of this project's build process, ensuring that you have the latest version and any custom modifications needed for this project.

### Build (Linux) (Partially working)
```bash
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
cd build
make -j$(nproc)
./NSPi
```

## License
This project is licensed under the GNU General Public License v3.0. See the [LICENSE](LICENSE) file for details.
