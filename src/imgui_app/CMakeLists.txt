
add_library(imgui_app)

set(BACKEND_SRC "")
if(IMGUI_BACKEND STREQUAL "SDL")
    set(BACKEND_SRC ${CMAKE_CURRENT_LIST_DIR}/backend/backend_sdl.cpp)
else()
    set(BACKEND_SRC ${CMAKE_CURRENT_LIST_DIR}/backend/backend_glfw.cpp)
endif()

target_include_directories(imgui_app
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/backend
        ${CMAKE_CURRENT_LIST_DIR}/config
        ${CMAKE_CURRENT_LIST_DIR}/core
        ${CMAKE_CURRENT_LIST_DIR}/ui
)

target_sources(imgui_app
    PUBLIC
        ${BACKEND_SRC}
        ${CMAKE_CURRENT_LIST_DIR}/core/app.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ui/ui_main.cpp
)

target_link_libraries(imgui_app
    imgui
    project_info
)

target_compile_definitions(imgui_app PRIVATE ${COMPILE_DEFS})
