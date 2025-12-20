cmake_minimum_required(VERSION 4.0)
project(geom_visualizer LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(geom_visualizer
        src/main.cpp
        src/glad.c
        src/main.cpp
)

target_include_directories(geom_visualizer PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_package(glfw3 REQUIRED)
target_link_libraries(geom_visualizer PRIVATE glfw dl GL)