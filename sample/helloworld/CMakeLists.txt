# CMakeList.txt : CMake project for smoothy, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# general configuration
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find Eigen3
find_package(Eigen3 3.3.5)
include_directories(${EIGEN3_INCLUDE_DIRS})

# enable Intel-MKL
set(MKL_DIR "/opt/intel/mkl")
set(MKL_INCLUDE_DIRS "${MKL_DIR}/include")
set(MKL_LIB_DIRS "${MKL_DIR}/lib/intel64")

find_library(LIB_MKL_RT NAMES mkl_rt HINTS ${MKL_LIB_DIRS})
find_library(LIB_PTHREAD NAMES pthread)

set(MKL_LIBRARY
	${LIB_MKL_RT}
	${LIB_PTHREAD})
include_directories(${MKL_INCLUDE_DIRS})

add_definitions(-DEIGEN_USE_MKL_ALL)

# Add source to this project's executable.
add_executable (helloworld_${CMAKE_CONF} "main.cpp")
