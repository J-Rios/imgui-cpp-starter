
### Project Libraries & Tools Dependencies ###

####################################################################################################

### Setup Configuration ###

message(STATUS "Get/Update project dependencies, please wait...")

include(FetchContent)

# Setup Project Dependecies Fetch Path variables
set(DIR_DEPS_LIB ${CMAKE_SOURCE_DIR}/deps/libraries)
set(DIR_DEPS_TOOL ${CMAKE_SOURCE_DIR}/deps/tools)

####################################################################################################

### Libraries To Fetch - GLFW ###

if(IMGUI_BACKEND STREQUAL "GLFW")
    message(STATUS "Fetching GLFW...")
    set(GLFW_SHARED ON CACHE BOOL "" FORCE)
    FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4
        SOURCE_DIR ${DIR_DEPS_LIB}/glfw
    )
    FetchContent_MakeAvailable(glfw)
endif()

####################################################################################################

### Libraries To Fetch - SDL2 ###

if(IMGUI_BACKEND STREQUAL "SDL")
    message(STATUS "Fetching SDL...")
    FetchContent_Declare(
        SDL2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-2.32.10
        SOURCE_DIR ${DIR_DEPS_LIB}/sdl
    )
    FetchContent_MakeAvailable(SDL2)
endif()

####################################################################################################

### Libraries To Fetch - Dear Imgui ###

message(STATUS "Fetching Dear Imgui...")
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui
    GIT_TAG v1.92.5-docking
    SOURCE_DIR ${DIR_DEPS_LIB}/imgui
)
#FetchContent_MakeAvailable(imgui)

FetchContent_GetProperties(imgui)
if(NOT imgui_POPULATED)
    FetchContent_MakeAvailable(imgui)

    set(IMGUI_SRC
        ${IMGUI_CORE}
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp
    )

    set(IMGUI_LINK "")

    if(IMGUI_BACKEND STREQUAL "GLFW")
        set(IMGUI_SRC
            ${IMGUI_SRC}
            ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
            ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
        )

        set(IMGUI_LINK
            glfw
            OpenGL::GL
        )
    endif()

    if(IMGUI_BACKEND STREQUAL "SDL")
        set(IMGUI_SRC
            ${IMGUI_SRC}
            ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl2.cpp
            ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
        )

        set(IMGUI_LINK
            SDL2::SDL2
            OpenGL::GL
        )
    endif()

    add_library(imgui ${IMGUI_SRC})

    target_include_directories(imgui PUBLIC
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
    )

    target_link_libraries(imgui PUBLIC ${IMGUI_LINK})

endif()

####################################################################################################

### Libraries To Fetch - ... ###

#
# Add Here More Libraries...
# ...

####################################################################################################

### Tools To Fetch - ... ###

#
# Add Here More Tools...
# ...

####################################################################################################
