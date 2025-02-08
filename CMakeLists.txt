# Minimum required version of CMake
cmake_minimum_required(VERSION 3.21)

# Project name
project(DiningPhilosophersProblem)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add subdirectories
add_subdirectory(src)
