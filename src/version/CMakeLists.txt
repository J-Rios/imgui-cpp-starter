
add_library(app_version_info)

target_include_directories(app_version_info
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/src
)

target_sources(app_version_info
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/src/version.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/version.h
)
