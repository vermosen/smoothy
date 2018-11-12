# CMakeList.txt : CMake project for smoothy, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.12)

project(smoothy)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(smoothy)
add_subdirectory(sample)
add_subdirectory(test)
