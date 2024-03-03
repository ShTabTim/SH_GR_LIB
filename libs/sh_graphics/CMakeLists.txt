cmake_minimum_required(VERSION 3.8)

project(sh_graphics_lib VERSION 1.0.0)

add_library(${PROJECT_NAME}
    STATIC
	"renderable.hpp"
	"renderable.cpp"
	"painting/uint_t3.cpp"
	"painting/uint_t3.hpp"
	"painting/drawable.hpp"
	"painting/drawable.cpp"
	"painting/paintives.hpp"
	"painting/paintives.cpp"
	)
    
add_library(sh_libs::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC 
	"painting/paintives.hpp"
	"renderable.hpp"
)