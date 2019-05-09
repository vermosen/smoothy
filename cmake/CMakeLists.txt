
cmake_minimum_required (VERSION 3.12 FATAL_ERROR)

include_guard(GLOBAL)

include("${CMAKE_CURRENT_LIST_DIR}/configuration/CMakeLists.txt")
include("${CMAKE_CURRENT_LIST_DIR}/vcs/CMakeLists.txt")
include("${CMAKE_CURRENT_LIST_DIR}/conan/CMakeLists.txt")
include("${CMAKE_CURRENT_LIST_DIR}/swig/CMakeLists.txt")
