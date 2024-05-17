cmake_minimum_required(VERSION 3.15.0)
project(sorting_algorithms CXX)

set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")

add_executable(insertion_sort insertion_sort.cpp)
add_executable(binary_add binary_add.cpp)
add_executable(selection_sort selection_sort.cpp)
add_executable(merge_sort merge_sort.cpp)
add_executable(binary_search binary_search.cpp)
add_executable(bubble_sort bubble_sort.cpp)