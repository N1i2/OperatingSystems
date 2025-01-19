cmake_minimum_required(VERSION 3.29)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

project(OS09_01)
project(OS09_02)
project(OS09_03)
project(OS09_04)

add_executable(OS09_01 src/OS09_01.cpp)
add_executable(OS09_02 src/OS09_02.cpp)
add_executable(OS09_03 src/OS09_03.cpp)
add_executable(OS09_04 src/OS09_04.cpp)
