cmake_minimum_required(VERSION 3.6)
project(localAssignmentC)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c MammalSightings.h ReadInData.c DataCalculations.c ReadOutData.c)
add_executable(localAssignmentC ${SOURCE_FILES})
