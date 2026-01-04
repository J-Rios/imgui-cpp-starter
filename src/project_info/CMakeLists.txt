
add_library(project_info)

target_include_directories(project_info
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

target_sources(project_info
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/project_info.cpp
        ${CMAKE_CURRENT_LIST_DIR}/project_info.h
)
