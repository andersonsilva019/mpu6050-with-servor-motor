# Copyright (c) 2023 Robarm
# All rights reserved

# cmake .. -D CMAKE_C_COMPILER=arm-linux-gnueabihf-gcc -D CMAKE_CXX_COMPILER=arm-linux-gnueabihf-g++
set(CMAKE_C_COMPILER arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++)

cmake_minimum_required(VERSION ${CMAKE_VERSION})
project("Robotic Arm" C CXX)

set(robarm_dir ${PROJECT_SOURCE_DIR})

add_subdirectory(${robarm_dir}/hal)
add_subdirectory(${robarm_dir}/module)
add_subdirectory(${robarm_dir}/utils)
add_subdirectory(${robarm_dir}/main)
# add_subdirectory(${robarm_dir}/test)
