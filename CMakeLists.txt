### Project General CMake File ###

###############################################################################

### CMake General Configuration ###

cmake_minimum_required(VERSION 3.29)

###############################################################################

### Project Configuration ###

# Project Name
set(PROJECT_NAME imguiapp)
project(${PROJECT_NAME} LANGUAGES ASM C CXX)

# Project Directory Paths
set(DIR_BIN ${CMAKE_SOURCE_DIR}/bin)
set(DIR_BUILD ${CMAKE_SOURCE_DIR}/build)
set(DIR_DOC ${CMAKE_SOURCE_DIR}/doc)
set(DIR_INC ${CMAKE_SOURCE_DIR}/include)
set(DIR_SRC ${CMAKE_SOURCE_DIR}/src)
set(DIR_LIB ${CMAKE_SOURCE_DIR}/lib)
set(DIR_TOOL ${CMAKE_SOURCE_DIR}/tool)
set(DIR_CMAKE_TOOLCHAIN ${CMAKE_SOURCE_DIR}/toolchain)

###############################################################################

### Build Options ###

# Target Build Platform OS
set(TARGET_PLATFORM "Linux" CACHE STRING "Target Build: Linux/Windows/Mingw") 
set_property(CACHE TARGET_PLATFORM PROPERTY STRINGS Linux Windows Mingw)

# Dear Imgui Backend to use
set(IMGUI_BACKEND "SDL" CACHE STRING "Backend for Dear ImGui")
set_property(CACHE IMGUI_BACKEND PROPERTY STRINGS "SDL" "GLFW")

###############################################################################

### Check For Required Tools ###

# Mandatory required tools
find_package(OpenGL REQUIRED)
if(TARGET_PLATFORM STREQUAL "Linux")
    find_package(X11 REQUIRED)
endif()

###############################################################################

### Build Setup ###

# Project C Version to use
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Project C++ Version to use
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Software Version
set(VERSION_X 1)
set(VERSION_Y 0)
set(VERSION_Z 0)

# Build Development Version
if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(VERSION_DEV true)
else()
    set(VERSION_DEV false)
endif()

# Set Version String
set(VERSION v_${VERSION_X}_${VERSION_Y}_${VERSION_Z})
if(VERSION_DEV)
    set(VERSION ${VERSION}_dev)
endif()

# Set Project build output binary name
set(PROJECT_OUT ${PROJECT_NAME}_${VERSION})

# Set build output directory
set(DIR_OUT_BIN ${DIR_BIN})
if(TARGET_PLATFORM STREQUAL "Linux")
    set(DIR_OUT_BIN ${DIR_OUT_BIN}/linux)
elseif(TARGET_PLATFORM STREQUAL "Mingw" OR TARGET_PLATFORM STREQUAL "Windows")
    set(DIR_OUT_BIN ${DIR_OUT_BIN}/windows)
else()
    message(STATUS FATAL_ERROR "Undefined Target Platform")
endif()
if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(DIR_OUT_BIN ${DIR_OUT_BIN}/debug)
else()
    set(DIR_OUT_BIN ${DIR_OUT_BIN}/release)
endif()
if(IMGUI_BACKEND STREQUAL "SDL")
    set(DIR_OUT_BIN ${DIR_OUT_BIN}/sdl)
elseif(IMGUI_BACKEND STREQUAL "GLFW")
    set(DIR_OUT_BIN ${DIR_OUT_BIN}/glfw)
endif()
set(DIR_OUT_BIN ${DIR_OUT_BIN}/${PROJECT_OUT})

###############################################################################

### Compile Definitions (Global Defines -DFLAG=X) ###

set(COMPILE_DEFS)

# Debug Version
if(CMAKE_BUILD_TYPE MATCHES Debug)
    list(APPEND COMPILE_DEFS DEBUG=1)
endif()

# Common Build
#list(APPEND COMPILE_DEFS
#    #FLAG=1
#    # ...
#)

###############################################################################

### Show Build Configuration ###

# Header
message(STATUS "---------------------------------------")
message(STATUS "Project:         ${PROJECT_NAME}")
message(STATUS "Target Platform: ${TARGET_PLATFORM}")

# Build Type
if(CMAKE_BUILD_TYPE MATCHES Debug)
    message(STATUS "Build Type:      Debug")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    message(STATUS "Build Type:      Release")
else()
    message(STATUS "Build Type:      Unkwown")
endif()

# Build Version
message(STATUS "Version:         ${VERSION}")

# Imgui Backend
if(IMGUI_BACKEND STREQUAL "SDL")
    message(STATUS "ImGui Backend: SDL2 + OpenGL3")
elseif(IMGUI_BACKEND STREQUAL "GLFW")
    message(STATUS "Imgui Backend: GLFW + OpenGL3")
else()
    message(STATUS FATAL_ERROR "Imgui Backend: Undefined")
endif()

message(STATUS "C Standard:      ${CMAKE_C_STANDARD}")
message(STATUS "C++ Standard:    ${CMAKE_CXX_STANDARD}")

# Show Compile Definitions
message(STATUS "Compile definitions:")
foreach(def ${COMPILE_DEFS})
    message(STATUS "    ${def}")
endforeach()

# Footer
message(STATUS "---------------------------------------")

###############################################################################

### Project Library Dependencies ###

# Run CMakeDeps to get/update project dependencies (libraries, tools, etc)
include(CMakeDeps.cmake)

###############################################################################

### Build Target ###

# Sources files
set(SRC_FILES
    ${DIR_SRC}/main.cpp
)

# Build executable binary
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Add headers directories
target_include_directories(${PROJECT_NAME} PUBLIC ${DIR_INC})

# Add subdirectories
add_subdirectory(src/imgui_demo)
add_subdirectory(src/version)
# ...

# Add Compile Definitions
target_compile_definitions(${PROJECT_NAME} PRIVATE ${COMPILE_DEFS})

# Libraries for linkage (-lLIBRARY)
target_link_libraries(${PROJECT_NAME}
    app_version_info
    imgui
    imgui_demo
)
if(TARGET_PLATFORM STREQUAL "Mingw" OR TARGET_PLATFORM STREQUAL "Windows")
    target_link_libraries(${PROJECT_NAME}
        version
    )
endif()

# Set Compiler Flags
target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<COMPILE_LANGUAGE:C>:${C_FLAGS}>
    $<$<COMPILE_LANGUAGE:CXX>:${CXX_FLAGS}>
)

# Set Linker Flags
target_link_options(${PROJECT_NAME} PRIVATE ${LINK_FLAGS})

# Set build target properties
set_target_properties(${PROJECT_NAME}
    PROPERTIES
    C_STANDARD ${CMAKE_C_STANDARD}
    CXX_STANDARD ${CMAKE_CXX_STANDARD}
    CXX_EXTENSIONS OFF
    OUTPUT_NAME ${PROJECT_OUT}
)

###############################################################################

### Pre-Build Targets ###

# Write CMake Version variables into C/C++ code version file
configure_file(
    ${DIR_SRC}/version/src/version.cpp.in
    ${DIR_SRC}/version/src/version.cpp
    @ONLY
)

# Touch version.cpp file to force update __DATE__ and __TIME__ and rebuild it
add_custom_target(update_version
    ${CMAKE_COMMAND} -E touch ${DIR_SRC}/version/src/version.cpp
)

# Setup the Pre-Build Targets as dependencies to run before the Build
add_dependencies(${PROJECT_NAME}
    update_version
    # ...
)

###############################################################################

### Post-Build Targets ###

# Copy executable file to debug/ and bin/ directory
add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${DIR_OUT_BIN}"
    COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE:${PROJECT_NAME}>"
        "${DIR_BUILD}/${PROJECT_NAME}"
    COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE:${PROJECT_NAME}>"
        "${DIR_OUT_BIN}/"
    COMMENT "Copying output binary to debug/ and bin/ directories"
)

# Add Windows DLL libraries to output directory
# Note: If a library has not been built as shared library, this will fail
if(TARGET_PLATFORM STREQUAL "Mingw" OR TARGET_PLATFORM STREQUAL "Windows")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_RUNTIME_DLLS:${PROJECT_NAME}>" "${DIR_OUT_BIN}/"
        COMMAND_EXPAND_LISTS
        COMMENT "Copying project runtime DLLs libraries to output directory"
    )
endif()
if(TARGET_PLATFORM STREQUAL "Mingw")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${LIBGCC_DLL}" "${DIR_OUT_BIN}/"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${LIBSTDCPP_DLL}" "${DIR_OUT_BIN}/"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${LIBPTHREAD_DLL}" "${DIR_OUT_BIN}/"
        COMMENT "Copying MinGW runtime DLLs libraries to output directory"
    )
endif()

###############################################################################
