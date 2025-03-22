cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(glad)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

# Add the static library
add_library(glad STATIC "${MY_SOURCES}")

# Include directories for the library
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
