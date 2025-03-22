cmake_minimum_required(VERSION 3.31)
include(FetchContent)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#project
project(imgui)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_C_COMPILER gcc)

# Define MY_SOURCES to be a list of all the source files for my project
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

add_library(imgui "${MY_SOURCES}")

target_include_directories(imgui PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")

target_link_libraries(imgui PRIVATE)
