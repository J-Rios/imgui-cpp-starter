#!/usr/bin/env bash

##############################################################################

### Functions ###

# APT update function
apt_update()
{
    echo "-------------------------------------------------"
    echo " Updating Repositories"
    echo "-------------------------------------------------"
    apt-get update
    echo ""
}

# APT install package function
apt_install()
{
    if [ $# -gt 0 ]; then
        echo "-------------------------------------------------"
        echo " Installing ${1} package"
        echo "-------------------------------------------------"
        apt-get -y install $1
        if [[ $? != 0 ]]; then
            echo "Error: Can't install ${1} package."
            echo ""
            exit 1
        fi
        echo ""
    fi
}

##############################################################################

### Main Script ###

# Check for permission
if [ "$(id -u)" != "0" ]; then
    echo "This script must be executed with administration privileges."
    echo ""
    exit 1
fi

# Installation
echo ""
echo "Installing Imgui Requirements for Ubuntu 24.04..."
echo ""
apt_update

# Common C/C++ development tools
apt_install build-essential
apt_install binutils
apt_install gcc
apt_install g++
apt_install gdb
apt_install mingw-w64
apt_install doxygen

# MinGW toolchain
apt_install mingw-w64

# Build system tools
apt_install cmake
apt_install make
apt_install pkg-config
apt_install ninja-build

# OpenGL dependencies
apt_install mesa-utils
apt_install libgl1-mesa-dev
apt_install libglu1-mesa-dev
apt_install libgl1-mesa-dev
apt_install libglu1-mesa-dev
apt_install mesa-common-dev
apt_install libxkbcommon-dev
apt_install libxrandr-dev
apt_install libxinerama-dev
apt_install libxcursor-dev
apt_install libxi-dev
apt_install libunwind-dev

# Wayland support
apt_install wayland-protocols
apt_install libwayland-dev
apt_install libdecor-0-dev

# Runtime libraries for ImGui backends
apt_install libglfw3
apt_install libsdl2-2.0-0

echo ""
echo "Installation completed"
echo ""

exit 0

##############################################################################
