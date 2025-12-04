
### CMake Windows Clang/LLVM Toolchain ###

###############################################################################

### Toolchain Setup ###

# Set System and Compiler
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_LINKER lld-link)

# Clear all default under-the-hood compiler flags applied by CMake
set(CMAKE_CXX_FLAGS_RELEASE)
set(CMAKE_C_FLAGS_RELEASE)
set(CMAKE_CXX_FLAGS_DEBUG)
set(CMAKE_C_FLAGS_DEBUG)

###############################################################################

### Compiler Configuration-Optimization Flags ###

# Common Flags
set(COMMON_FLAGS)
list(APPEND COMMON_FLAGS
    -Wall
    -Wextra
    -Wpedantic
    -pedantic
#   -Werror
    -Wshadow
    -Wconversion
    -Wparentheses
    -Wcast-align
    -Wmissing-declarations
    -Wredundant-decls
    -Wimplicit-fallthrough
)

# Optimization Flags
set(OPTIMIZATION_FLAGS)
list(APPEND OPTIMIZATION_FLAGS
    -ffunction-sections
    -fdata-sections
#   -flto
)
if(CMAKE_BUILD_TYPE MATCHES Debug)
    list(APPEND OPTIMIZATION_FLAGS
        -O0
        -g
    )
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    list(APPEND OPTIMIZATION_FLAGS
        -Os
    )
endif()

# C Flags
set(C_FLAGS)
list(APPEND C_FLAGS
    ${COMMON_FLAGS}
    ${OPTIMIZATION_FLAGS}
    -Wmissing-prototypes
    -Wstrict-prototypes
)

# C++ Flags
set(CXX_FLAGS)
list(APPEND CXX_FLAGS
    ${COMMON_FLAGS}
    ${OPTIMIZATION_FLAGS}
    -Wconditionally-supported
    -Wno-variadic-macros
)

# Linker Flags
set(LINK_FLAGS)
list(APPEND LINK_FLAGS
    -Wl,/INCLUDE:__chkstk
)
if(CMAKE_BUILD_TYPE MATCHES Release)
    list(APPEND LINK_FLAGS
        -Wl,/OPT:REF
        -Wl,/OPT:ICF
        -Wl,/DEBUG:NONE
    )
endif()

# Set Static/Dynamic Linkage
if(BUILD_STATIC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
else()
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
endif()

###############################################################################
