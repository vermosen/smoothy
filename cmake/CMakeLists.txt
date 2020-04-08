cmake_minimum_required (VERSION 3.13)

include_guard(GLOBAL)

message(STATUS   "\n")
message(STATUS   ":==================================:")
message(STATUS   ":setting global cmake configuration:")
message(STATUS   ":==================================:\n")

message(STATUS "*** configuration set to \"${CMAKE_BUILD_TYPE}\" ***")

IF(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
   message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
   FILE(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.15/conan.cmake"
                 "${CMAKE_BINARY_DIR}/conan.cmake")
ENDIF()

INCLUDE(${CMAKE_BINARY_DIR}/conan.cmake)

conan_check(VERSION 1.12.0 REQUIRED)

set(EIGEN_VERS    "3.3.7" )
set(BOOST_VERS    "1.72.0")
set(PFR_VERS      "1.0.0" )

# enable the languages
enable_language(C CXX CUDA)

# dialect
set(CMAKE_CXX_STANDARD ${CXX_DIALECT})

# load the utils module
INCLUDE("${CMAKE_CURRENT_LIST_DIR}/module/utils.cmake")

# set verbosity
if(VERBOSE)
    set(CMAKE_VERBOSE_MAKEFILE ON)
endif()

set(THREADS_PREFER_PTHREAD_FLAG ON)
message(STATUS "THREADS_PREFER_PTHREAD_FLAG value: ${THREADS_PREFER_PTHREAD_FLAG}")
FIND_PACKAGE(Threads)

# set the compiler flags
message(STATUS "CMAKE_BUILD_TYPE set to ${CMAKE_BUILD_TYPE}")

# set the PIC/PIE flag
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
message(STATUS "CMAKE_POSITION_INDEPENDENT_CODE set to ${CMAKE_POSITION_INDEPENDENT_CODE}")

# check for LTO support
include(CheckIPOSupported)
check_ipo_supported(RESULT LTO_SUPPORTED)

if(LTO_SUPPORTED)
	if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	# -g and -lto support is still eperimental in gcc
	else()

		message(DEBUG "LTO enabled")
		set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
	endif()
endif()

# build flags
if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")

	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -DDEBUG -g")
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Profiling")

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg -O3 -DNDEBUG")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg -O3 -DNDEBUG")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pg -O3 -DNDEBUG")

elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -DNDEBUG")
endif()

string(TOLOWER ${CMAKE_BUILD_TYPE} LC_BUILD_TYPE)
set(INSTALL_BIN_DIR ${CMAKE_INSTALL_PREFIX}/bin/${LC_BUILD_TYPE})
set(INSTALL_LIB_DIR ${CMAKE_INSTALL_PREFIX}/lib/${LC_BUILD_TYPE})

message(DEBUG "INSTALL_BIN_DIR set to ${INSTALL_BIN_DIR}")
message(DEBUG "INSTALL_LIB_DIR set to ${INSTALL_LIB_DIR}")
