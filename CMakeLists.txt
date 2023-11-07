cmake_minimum_required(VERSION 3.13)

project(Ray LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

set (SOURCE_RAY

    src/vec3.h
    src/ray.h
    src/color.h
    src/camera.h
    src/hittable.h
    src/sphere.h
    src/hittable_list.h
    src/rtweekend.h
    src/interval.h
    src/material.h
    src/main.cpp
)

include_directories(src)

message (STATUS "Compiler ID: " ${CMAKE_CXX_COMPILER_ID})

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wnon-virtual-dtor)
    add_compile_options(-Wreorder)
    add_compile_options(-Wmaybe-uninitialized)
    add_compile_options(-Wunused-variable)  

endif()

add_executable(Ray ${SOURCE_RAY})