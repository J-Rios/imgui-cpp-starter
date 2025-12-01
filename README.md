# imgui-cpp-starter

Base project in C++ prepared to be used as starting point to build Dear Imgui applications!

It provides a complete setup using **CMake** (as build system generator) and **Ninja** (as build system), supports multiple platforms and ImGui backends, and includes ready-to-use integration with **VSCode**.

## Key Features

- **CMake + Ninja** build workflow.
- **CMakePresets** for Linux, Windows, and cross-compiling to Windows from Linux using MinGW.
- Support for the most common ImGui backends:  
  **OpenGL + SDL2** and **OpenGL + GLFW**.
- Fully prepared for **VSCode** (build, run, debug).
- Automatic dependency fetching via **CMake FetchContent**.
- Clean directory structure with isolated build folders per platform/configuration/backend.

---

## Requirements

The following commands install all required tools on **Ubuntu 24.04**.  
For other distributions or operating systems, find and install the equivalent packages.

1. Update APT repositories

```bash
sudo apt update
```

2. Common C/C++ development tools:

```bash
sudo apt install -y build-essential binutils gcc g++ gdb mingw-w64 doxygen
```

3. MinGW toolchain (only needed for cross-compiling to Windows from Linux):

```bash
sudo apt install -y mingw-w64
```

4. Build system tools:

```bash
sudo apt install -y cmake make pkg-config ninja-build
```

5. OpenGL dependencies (required by the ImGui backends):

```bash
sudo apt install -y mesa-utils libgl1-mesa-dev libglu1-mesa-dev libgl1-mesa-dev libglu1-mesa-dev mesa-common-dev libxkbcommon-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libunwind-dev
```

6. Optional Wayland support:

```bash
sudo apt install wayland-protocols libwayland-dev libdecor-0-dev
```

7. Runtime libraries for ImGui backends:

```bash
# For GLFW builds
sudo apt install -y libglfw3

# For SDL builds
sudo apt install -y libsdl2-2.0-0
```

## VSCode Usage

- Build: Launch **"Build & Compile"** by pressing **F7** key.
- Run/Debug: Launch **"Run & Debug"** by pressing **F5** key.

## Project Configuration

- Modify CMakeLists.txt to adjust global project settings.

- Project dependencies are declared in CMakeDeps.cmake and automatically downloaded into the deps/ directory.

- All CMake presets define:
    - Target platform (Linux, Windows, or MinGW for cross-compiling)
    - Build type (Debug / Release)
    - ImGui backend (SDL or GLFW)

- Generated binaries are placed under:
    - build/<platform>-<config>/<backend>
    - bin/<platform>-<config>/<backend>

## Additional Notes

All build and configuration presets are defined in **CMakePresets.json**.

Building from the terminal:

```bash
cmake --preset <preset_name>
cmake --build --preset <preset_name>
```

This project is designed to quickly bootstrap portable, structured ImGui applications for different platforms.
