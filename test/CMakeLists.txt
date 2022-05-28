cmake_minimum_required(VERSION 3.0.0)
project(NmkTests VERSION 0.1.0)


add_executable(NmkTests Tests.cpp)
target_link_libraries(NmkTests PUBLIC gtest_main nmkSolver)

add_test(
    NAME NmkTests 
    COMMAND NmkTests 
)