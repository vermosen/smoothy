
cmake_minimum_required (VERSION 3.12 FATAL_ERROR)



# general configuration
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include
include(GNUInstallDirs)
include(CheckCXXCompilerFlag)

MESSAGE(STATUS "info: CMAKE_CXX_STANDARD set to ${CMAKE_CXX_STANDARD} --")
MESSAGE(STATUS "info: CMAKE_CXX_STANDARD_REQUIRED set to ${CMAKE_CXX_STANDARD_REQUIRED} --")

if(CMAKE_PROFILE STREQUAL "gcc7")
	include("${CMAKE_CURRENT_LIST_DIR}/gcc7/CMakeLists.txt")
elseif(CMAKE_PROFILE STREQUAL "clang5")
	include("${CMAKE_CURRENT_LIST_DIR}/clang5/CMakeLists.txt")
else()
	MESSAGE(FATAL_ERROR "Unknown configuration passed")
endif()
