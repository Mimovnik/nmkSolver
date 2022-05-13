cmake_minimum_required(VERSION 3.0.0)
project(nmkSolver VERSION 0.1.0)


add_library(
    SOURCE_FILES

    src/Commands.h
    src/Commands.cpp
)
add_executable(nmkSolver src/main.cpp)
target_link_libraries(${PROJECT_NAME} SOURCE_FILES)
