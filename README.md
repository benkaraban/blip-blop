# Blip'n Blop - Modernized & Fixed

This repository contains a modernized version of the 2002 classic **Blip'n Blop**. This version has been updated to run on modern Windows and Linux systems, addressing several long-standing issues in the original code and previous ports.

## Significant Corrections & Modernization

### 1. Linux Compatibility & Path Handling
The original game and its subsequent ports used backslashes (`\`) for asset paths, which are hardcoded into the binary level files (`.lvl`). This caused the game to fail to load levels and assets on Linux and other POSIX-compliant systems.
- **Fix**: Implemented a `fixPath` utility that dynamically normalizes paths during the level loading process, ensuring compatibility with Linux file systems without needing to modify the binary data files.

### 2. Resolution & Windowing Fixes
The previous SDL2 port had hardcoded window positioning and fixed small resolutions that didn't play well with modern displays.
- **Centering**: The game window now uses `SDL_WINDOWPOS_CENTERED` to prevent it from appearing in the corner of the screen or off-screen.
- **Logical Scaling**: Added `SDL_RenderSetLogicalSize`. The game now maintains its internal 640x480 logic and aspect ratio while allowing the window to be resized. This effectively "unlocks" the game from its original resolution, allowing it to scale beautifully on 4K or ultra-wide monitors.
- **Modern Fullscreen**: Switched to `SDL_WINDOW_FULLSCREEN_DESKTOP`, providing a smoother transition and better compatibility with modern OS window managers compared to legacy "exclusive" fullscreen modes.

### 3. Build System Overhaul (CMake)
The build system was previously fragmented and contained Windows-specific assumptions that broke the build on Linux.
- **Improvements**: Updated `CMakeLists.txt` to use standard CMake package finders for SDL2 and SDL2_mixer. Removed hardcoded `WIN32` flags for Linux builds, ensuring a clean compilation process across different platforms.

### 4. Continuous Integration (CI) Fixes
The AppVeyor CI pipeline was broken due to an environment misconfiguration during the `vcpkg` dependency setup.
- **Fix**: Configured global Git user identity in the CI environment to allow the automated setup of dependencies to proceed without manual intervention.

## Technical Details

- **Core**: C++ (Modernized)
- **Multimedia**: SDL2, SDL2_mixer
- **Sound Engine Wrapper**: FMOD-to-SDL bridge (Modernized)
- **Build Tool**: CMake 3.1+

## Building the Project

### Linux
1. Install dependencies: `libsdl2-dev`, `libsdl2-mixer-dev`, `cmake`.
2. Run:
   ```bash
   mkdir build && cd build
   cmake ../vc-projects/Blip_n_Blop_3
   make
   ```

### Windows
1. Use Visual Studio with CMake support.
2. Dependencies are managed via `vcpkg` (see [AppVeyor config](.appveyor.yml) for details).

---
*Kudos to the original creators and the community for keeping this gem alive!*
