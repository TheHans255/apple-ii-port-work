# Apple //e LLVM-MOS Port Work

This is a repository containing work for building up a port of [LLVM-MOS](https://llvm-mos.org/)
to the Apple //e as a build target.

## Dev Requirements

- [CMake](https://cmake.org/)
- The [LLVM-MOS SDK](https://github.com/llvm-mos/llvm-mos-sdk), downloaded to a directory of your choice
- A suitable Apple //e emulator, such as [AppleWin](https://github.com/AppleWin/AppleWin)
  OR a real Apple //e device (Apple //e, //c, IIgs in emulation mode, or compatible clone)
  with a disk transfer program such as [ADTPro](https://adtpro.com/)
- A bootable [ProDOS 8](https://prodos8.com/) disk image. The latest version, ProDOS 2.4.2,
  is [available for download on ProDOS's website](https://prodos8.com/releases/prodos-242/).
- A program for manipulating Apple disk images compatible with your dev machine, such as
  [AppleCommander](https://applecommander.github.io/)

## Build Steps

1. When you first clone the repository, or change any of the CMake files, execute
   `$ cmake -D CMAKE_C_COMPILER="/path/to/mos-common-clang" -S src -B build` in the root of the repository,
   where `/path/to/mos-common-clang` is the path to `mos-common-clang` in your LLVM-MOS SDK installation.
2. For each change, execute `$ make -C build` from the root of the repository
3. Find the example you want to load as `build/example/<example name>/<example name>.sys`
4. Using your disk manipulation program, import that `.sys` file to the root of the ProDOS disk.
5. Load the disk in the emulator (or transfer it to the real device), boot it,
   and select your chosen `.sys` program in the menu.

## Goals

**Core goals:**

- Allow basic CLI C applications to be written for the Apple //e
- Allow file access through ProDOS

**Advanced goals:**

- Port stdio and stdlib to ProDOS for reading files
- Expose all available system calls to the user, including Monitor graphics routines
- Berkeley Sockets implementation for Uthernet I and II
- Allow alternate linking strategies for:
  - Access to HiRes
  - Building dynamically linked machine language subroutines for BASIC