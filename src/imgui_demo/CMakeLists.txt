
add_library(imgui_demo)

target_include_directories(imgui_demo
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

if(IMGUI_BACKEND STREQUAL "SDL")
    target_sources(imgui_demo
        PUBLIC
            ${CMAKE_CURRENT_LIST_DIR}/imgui_demo_sdl.cpp
    )
else()
    target_sources(imgui_demo
        PUBLIC
            ${CMAKE_CURRENT_LIST_DIR}/imgui_demo_glfw.cpp
    )
endif()

target_link_libraries(imgui_demo
    imgui
)
