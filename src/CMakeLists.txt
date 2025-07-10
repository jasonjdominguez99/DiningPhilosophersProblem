# Minimum required version of CMake
cmake_minimum_required(VERSION 3.21)

# Project name
project(DiningPhilosophersProblem)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Only disable Apple-specific flags if using GCC on macOS
if(APPLE AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(STATUS "Using GCC on macOS - disabling Apple-specific flags")
    set(CMAKE_OSX_ARCHITECTURES "")
    set(CMAKE_OSX_SYSROOT "")
    set(CMAKE_OSX_DEPLOYMENT_TARGET "")
endif()

# Add all the source files for your project
add_executable(DiningPhilosophersProblem
    main.cpp
    AbstractPhilosopher.cpp
    SelfishPhilosopher.cpp
    OrderedPhilosopher.cpp
    PhilosophersFactory.cpp
    SimulationArgParser.cpp
)
