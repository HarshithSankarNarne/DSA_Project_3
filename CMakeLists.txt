cmake_minimum_required(VERSION 3.31)
project(Project_3)

set(CMAKE_CXX_STANDARD 14)
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

add_executable(Project_3 main.cpp
        Benchmark.cpp
        Benchmark.h
        Task.h)
