# CMakeList.txt : CMake project for smoothy, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.12 FATAL_ERROR)

MESSAGE(STATUS "info: project build type set to ${CMAKE_BUILD_TYPE} --")

include("cmake/CMakeLists.txt")

SET(PROJECT_NAME "smoothy"					 CACHE STRING "Project Name"			)
SET(PROJECT_NAMESPACE "smoothy"				 CACHE STRING "Project Namespace"		)
SET(PROJECT_HOME "${CMAKE_CURRENT_LIST_DIR}" CACHE STRING "Project Home directory"	)

string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_U)
SET(${PROJECT_NAME_U}_MAJOR_VERSION  0)
SET(${PROJECT_NAME_U}_MINOR_VERSION  0)
SET(${PROJECT_NAME_U}_PATCH_VERSION  1)

MESSAGE(STATUS "project version set to ${${PROJECT_NAME_U}_VERSION}")

project(
	"${PROJECT_NAME}"
	LANGUAGES C CXX
	VERSION	"${${PROJECT_NAME_U}_VERSION}"
	DESCRIPTION "the smoothy project"
)

set(CMAKEPACKAGE_INSTALL_DIR
    "${CMAKE_INSTALL_DATADIR}/cmake"
    CACHE PATH "The directory relative to CMAKE_PREFIX_PATH where smoothy.cmake is installed"
)

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

include_directories("${PROJECT_HOME}/src")

add_subdirectory(sample)
add_subdirectory(unittestsuite)
add_subdirectory(smoothy)
