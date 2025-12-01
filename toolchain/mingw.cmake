
### CMake Linux Compiler Toolchain ###

###############################################################################

### Toolchain Setup ###

# Set System and Compiler
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
set(CMAKE_RC_COMPILER x86_64-w64-mingw32-windres)

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
    -DWIN32
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
    -Wimplicit-fallthrough=2
    -fdump-tree-optimized
    -fstack-usage
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
        -Og
        -ggdb
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
#   -static
#   -flto
    -Wl,-cref
    -Wl,--gc-sections
    -Wl,--print-memory-usage
)

###############################################################################
