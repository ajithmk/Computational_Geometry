cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 14)
project(segment_intersection)
include_directories(../common_libraries/Eigen ./include)
set(SOURCES ./src/main.cpp ./src/auxiliary.cpp ./src/myhdr_impl_.cpp)
set(CMAKE_BUILD_TYPE Debug)
add_executable(seg_intersection ${SOURCES})
