# CMakeList.txt : CMake project for smoothy, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.12)

if (CMAKE_BUILD_TYPE STREQUAL "debugasm")
	enable_language(ASM)
endif()

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

# gcc flags
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	target_compile_options(smoothytest_${CMAKE_CONF} INTERFACE -O0 -ggdb3 -DDEBUG)
elseif (CMAKE_BUILD_TYPE STREQUAL "DebugAsm")
	set_target_properties(smoothytest_${CMAKE_CONF} PROPERTIES COMPILE_FLAGS -save-temps)
	target_compile_options(smoothytest_${CMAKE_CONF} INTERFACE -O3 -DNDEBUG -flto -DDEBUG_ASM -S -masm=intel)
elseif (CMAKE_BUILD_TYPE STREQUAL "Profiling")
	target_compile_options(smoothytest_${CMAKE_CONF} INTERFACE -O3 -DNDEBUG -flto)
else (CMAKE_BUILD_TYPE STREQUAL "Release")
	target_compile_options(smoothytest_${CMAKE_CONF} INTERFACE -O3 -DNDEBUG -flto)
endif()
