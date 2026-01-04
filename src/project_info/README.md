# Project Information

This component provides an easy way to pass project information from the build system (i.e. CMake) to the C/C++ code.

Project information could be something like project name, build type, software version, etc.

To use this component:

1. The build system must parse and replace the @SOMETHING@ variables according to build information, for example CMake could use **configure_file()** to make this variable replacement:

```cmake
# Setup project_info
configure_file(
    ${CMAKE_SOURCE_DIR}/src/project_info/project_info.cpp.in
    ${CMAKE_SOURCE_DIR}/src/project_info/project_info.cpp
    @ONLY
)
```

2. Also, the build system must touch the project_info.cpp file each time a project build is requested, to ensure the GCC __DATE__ and __TIME__ variables are updated. For example, setup a pre-build target for that using CMake:

```cmake
# Touch project_info.cpp file to force update __DATE__ and __TIME__ and rebuild it
add_custom_target(update_project_info
    ${CMAKE_COMMAND} -E touch ${CMAKE_SOURCE_DIR}/src/project_info/project_info.cpp
)

# Setup the Pre-Build Targets as dependencies to run before the Build
add_dependencies(${PRJ_OUT_FILE}.elf update_project_info)
```
