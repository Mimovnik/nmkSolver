cmake_minimum_required(VERSION 3.0.0)
project(nmkSolver VERSION 0.1.0)

add_subdirectory(googletest)
enable_testing()

add_library(
    nmkSolver

    src/Commands.h
    src/Commands.cpp

    src/main.cpp
)

add_subdirectory(test)