cmake_minimum_required(VERSION 3.1)
project(speedo)
set(CMAKE_CXX_STANDARD 17)

# Specify locations of header files.
include_directories(include)

# Declare the test executable.
add_executable(speedo_test src/speedo_test.cpp)

