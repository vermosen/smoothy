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
if(    NOT cmake_build_type_tolower STREQUAL "debug"
   AND NOT cmake_build_type_tolower STREQUAL "release")
   message(FATAL_ERROR "Unknown build type \"${CMAKE_BUILD_TYPE}\". Allowed values are Debug, Release (case-insensitive).")
endif()

set(CMAKEPACKAGE_INSTALL_DIR
    "${CMAKE_INSTALL_DATADIR}/cmake"
    CACHE PATH "The directory relative to CMAKE_PREFIX_PATH where smoothy.cmake is installed"
    )

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

include(GNUInstallDirs)
include(CheckCXXCompilerFlag)

add_subdirectory(sample)
add_subdirectory(unittestsuite)
add_subdirectory(smoothy)
