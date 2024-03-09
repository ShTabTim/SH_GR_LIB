cmake_minimum_required(VERSION 3.8)

project(sh_graphics_lib VERSION 1.0.0)

add_library(${PROJECT_NAME}
    STATIC
	"painting/uint8_t.cpp"
	"painting/uint8_t.hpp"
	"painting/paintives.hpp"
	"painting/paintives.tpp"
	"renderables/meta_renderable.hpp"
	"renderables/meta_renderable.cpp"
	"renderables/winapi_renderable.cpp"
	"renderables/winapi_renderable.hpp"
	"painting/drawable.cpp"
	"painting/drawable.tpp"
	"painting/drawable.hpp"
)
    
add_library(sh_libs::${PROJECT_NAME} ALIAS ${PROJECT_NAME})