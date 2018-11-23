# CMakeList.txt : CMake project for smoothy, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.12)

# set debug target
if (CMAKE_CONF MATCHES "Debug")
	set(CMAKE_BUILD_TYPE Debug)
endif (CMAKE_CONF MATCHES "Debug")

find_library(LIB_SMOOTHY NAMES smoothy)

# add the project sources
file(GLOB source_files
            "*.h"
            "*.cpp"
            "tests/*.cpp"
            "tests/*.h"
    )

# Add source to this project's executable.
add_executable (smoothytest_${CMAKE_CONF} ${source_files})

target_include_directories(smoothytest_${CMAKE_CONF} INTERFACE
	"${SMOOTHY_INCLUDE_DIR}"
)

target_include_directories(smoothytest_${CMAKE_CONF} INTERFACE
	"${PROJECT_SOURCE_DIR}"
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
