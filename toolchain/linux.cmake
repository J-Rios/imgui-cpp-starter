
### CMake Linux Compiler Toolchain ###

###############################################################################

### Toolchain Setup ###

# Set System and Compiler
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

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
    -Wl,--gc-sections
)
if(BUILD_STATIC)
    list(APPEND LINK_FLAGS
        -static
    )
endif()
if(CMAKE_BUILD_TYPE MATCHES Release)
    list(APPEND LINK_FLAGS
    #   -flto
        -Wl,-strip-all
    )
endif()

###############################################################################
