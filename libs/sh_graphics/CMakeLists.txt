cmake_minimum_required(VERSION 3.8)

project(sh_graphics_lib VERSION 1.0.0)

add_library(${PROJECT_NAME}
    STATIC 
	"handle.hpp"
	"handle.cpp"
	"shwin.hpp"
	"shwin.cpp"
    ) 
    
add_library(sh_libs::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC 
	"handle.hpp"
	"shwin.hpp"
)