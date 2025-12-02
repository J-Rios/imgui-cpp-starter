
add_library(version_info)

target_include_directories(version_info
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

target_sources(version_info
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/version_info.cpp
        ${CMAKE_CURRENT_LIST_DIR}/version_info.h
)
