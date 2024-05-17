cmake_minimum_required(VERSION 3.15.0)
project(sorting_algorithms CXX)

set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")

add_executable(insertion insertion_sort.cpp)
add_executable(binary_add binary_add.cpp)
add_executable(selection selection_sort.cpp)
add_executable(merge merge_sort.cpp)
add_executable(binary_search binary_search.cpp)