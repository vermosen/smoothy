
cmake_minimum_required (VERSION 3.12 FATAL_ERROR)

# general configuration
include_guard(GLOBAL)

if(CMAKE_PROFILE STREQUAL "gcc7")
	include("${CMAKE_CURRENT_LIST_DIR}/gcc7/CMakeLists.txt")
elseif(CMAKE_PROFILE STREQUAL "clang5")
	include("${CMAKE_CURRENT_LIST_DIR}/clang5/CMakeLists.txt")
else()
	MESSAGE(FATAL_ERROR "Unknown configuration passed")
endif()
