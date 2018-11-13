# CMakeList.txt : CMake project for smoothy, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.12)

find_library(LIB_SMOOTHY NAMES smoothy)

# add the project sources
file(GLOB source_files
            "*.h"
            "*.cpp"
            "tests/*.cpp"
            "tests/*.h"
    )

# Add source to this project's executable.
add_executable (helloworld_${CMAKE_CONF} ${source_files})
