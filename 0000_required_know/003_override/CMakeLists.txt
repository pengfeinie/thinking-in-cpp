cmake_minimum_required (VERSION 2.8.7)
project (003_override)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")


add_executable(test_override_01 test_override_01.cpp)
add_executable(test_override_02 test_override_02.cpp)