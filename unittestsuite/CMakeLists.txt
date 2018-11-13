# CMakeList.txt : CMake project for smoothy, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.12)

# set debug target
if (CMAKE_CONF MATCHES "Debug")
	set(CMAKE_BUILD_TYPE Debug)
endif (CMAKE_CONF MATCHES "Debug")

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

find_library(LIB_SMOOTHY NAMES smoothy)

add_definitions(-DEIGEN_USE_MKL_ALL)

# add the project sources
file(GLOB source_files
            "*.h"
            "*.cpp"
            "tests/*.cpp"
            "tests/*.h"
    )

# Add source to this project's executable.
add_executable (unittest_${CMAKE_CONF} ${source_files})

target_include_directories(unittest_${CMAKE_CONF} INTERFACE
	"${SMOOTHY_INCLUDE_DIR}"
)

target_include_directories(unittest_${CMAKE_CONF} INTERFACE
	"${PROJECT_SOURCE_DIR}"
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
