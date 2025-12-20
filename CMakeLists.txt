cmake_minimum_required(VERSION 4.0)
project(untitled LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(untitled
        src/main.cpp
        src/glad.c
        src/main.cpp
)

target_include_directories(untitled PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_package(glfw3 REQUIRED)
target_link_libraries(untitled PRIVATE glfw dl GL)