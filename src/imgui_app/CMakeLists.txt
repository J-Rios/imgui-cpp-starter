
add_library(imgui_app)

target_include_directories(imgui_app
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

if(IMGUI_BACKEND STREQUAL "SDL")
    target_sources(imgui_app
        PUBLIC
            ${CMAKE_CURRENT_LIST_DIR}/imgui_app_sdl.cpp
    )
else()
    target_sources(imgui_app
        PUBLIC
            ${CMAKE_CURRENT_LIST_DIR}/imgui_app_glfw.cpp
    )
endif()

target_link_libraries(imgui_app
    imgui
    version_info
)
