cmake_minimum_required(VERSION 4.0)
project(geom_visualizer LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---------- Common include path ----------
set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# ---------- Put shared code into a library ----------
add_library(geom_core STATIC
        src/geom.cpp
)

target_include_directories(geom_core PUBLIC
        ${PROJECT_INCLUDE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/external/mdspan/include
)

add_library(visualizer_core STATIC
        src/visualizer.cpp
        src/glad.c
)

target_include_directories(visualizer_core PUBLIC
        ${PROJECT_INCLUDE_DIR}
)

find_package(glfw3 REQUIRED)
target_link_libraries(visualizer_core PRIVATE
        glfw
        dl
        GL
)

# ---------- App ----------
add_executable(geom_visualizer
        src/main.cpp
)

target_include_directories(geom_visualizer PRIVATE
        ${PROJECT_INCLUDE_DIR}
)

target_link_libraries(geom_visualizer PRIVATE
        geom_core
        visualizer_core
)

# ---------- Tests ----------
enable_testing()

add_executable(geom_test
        test/geom_tests.cpp
)

target_link_libraries(geom_test PRIVATE
        geom_core
)

# Ubuntu libgtest-dev: this *often* works
find_package(GTest REQUIRED)

target_link_libraries(geom_test PRIVATE
        GTest::gtest
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(geom_test)


add_executable(sfml_test src/sfml_test.cpp)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
target_link_libraries(sfml_test PRIVATE sfml-graphics sfml-window sfml-system)
