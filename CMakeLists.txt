cmake_minimum_required(VERSION 3.24)
project(sorting)

set(CMAKE_CXX_STANDARD 17)

add_executable(sorting main.cpp data_generation.cpp data_generation.h time_measurement.cpp time_measurement.h sorting_algorithms.h)
