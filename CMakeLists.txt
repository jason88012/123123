cmake_minimum_required(VERSION 3.0)
project(ErrorTracer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Create an executable for main_recursion.cpp
add_executable(error_tracer_recursion main_recursion.cpp)
target_compile_options(error_tracer_recursion PRIVATE -O2 -g)

# Create an executable for main_iteration.cpp
add_executable(error_tracer_iteration main_iteration.cpp)
target_compile_options(error_tracer_iteration PRIVATE -O2 -g)
