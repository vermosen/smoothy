# CMakeList.txt : CMake project for smoothy, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.12)

if (CMAKE_BUILD_TYPE STREQUAL "DebugAsm")
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
	add_definitions(-DDEBUG)
	target_compile_options(smoothytest_${CMAKE_CONF} INTERFACE -O0 -ggdb3)
elseif (CMAKE_BUILD_TYPE STREQUAL "DebugAsm")
	add_definitions(-DPRINT_ASM -DNDEBUG)
	set_target_properties(smoothytest_${CMAKE_CONF} PROPERTIES COMPILE_FLAGS -save-temps)
	target_compile_options(smoothytest_${CMAKE_CONF} INTERFACE -O3 -flto -d -S -masm=intel)
	target_link_libraries(smoothytest_${CMAKE_CONF} INTERFACE -flto)
elseif (CMAKE_BUILD_TYPE STREQUAL "Profiling")
	add_definitions(-DNDEBUG)
	target_compile_options(smoothytest_${CMAKE_CONF} INTERFACE -O3 -flto)
	target_link_libraries(smoothytest_${CMAKE_CONF} INTERFACE -flto)
else (CMAKE_BUILD_TYPE STREQUAL "Release")
	add_definitions(-DNDEBUG)
	target_compile_options(smoothytest_${CMAKE_CONF} INTERFACE -O3 -flto)
	target_link_libraries(smoothytest_${CMAKE_CONF} INTERFACE -flto)
endif()
