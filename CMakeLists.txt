# CMakeList.txt : CMake project for smoothy, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.12)

project(smoothy)

if (CMAKE_CONF)
	set(CMAKE_BUILD_TYPE "${CMAKE_CONF}")
endif()

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

string(TOLOWER "${CMAKE_BUILD_TYPE}" cmake_build_type_tolower)
if (cmake_build_type_tolower STREQUAL "debug")
	set(CMAKE_BUILD_TYPE Debug)
elseif (cmake_build_type_tolower STREQUAL "release")
	set(CMAKE_BUILD_TYPE Release)
elseif (cmake_build_type_tolower STREQUAL "profiling")
	set(CMAKE_BUILD_TYPE Profiling)
elseif (cmake_build_type_tolower STREQUAL "debugasm")
	set(CMAKE_BUILD_TYPE DebugAsm)
else ()
	message(FATAL_ERROR "Unknown build type \"${CMAKE_BUILD_TYPE}\". Allowed values are Debug, DebugAsm, Release, Profiling.")
endif()

set(CMAKEPACKAGE_INSTALL_DIR
    "${CMAKE_INSTALL_DATADIR}/cmake"
    CACHE PATH "The directory relative to CMAKE_PREFIX_PATH where smoothy.cmake is installed"
    )

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

include(GNUInstallDirs)
include(CheckCXXCompilerFlag)

# general configuration
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find boost
find_package(Boost)

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

add_subdirectory(sample)
add_subdirectory(unittestsuite)
add_subdirectory(smoothy)
