cmake_minimum_required(VERSION 3.8)

project(sh_graphics)

set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(${PROJECT_NAME} WIN32 "main.cpp")

add_subdirectory(libs/sh_graphics)
include_directories(libs/sh_graphics)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        sh_libs::sh_graphics_lib
    )