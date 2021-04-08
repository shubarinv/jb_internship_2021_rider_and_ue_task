cmake_minimum_required(VERSION 3.19)
project(jb_intShip_2021 CXX)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(libs/taskflow)
include_directories(src)
add_subdirectory(src)

include_directories(catch2_tests)
add_subdirectory(catch2_tests)