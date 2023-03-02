cmake_minimum_required(VERSION 3.1)
project(time_profiler)
set(CMAKE_CXX_STANDARD 17)

# Specify locations of header files.
include_directories(include)

# Declare the test executable.
add_executable(time_profiler_test src/time_profiler_test.cpp)

