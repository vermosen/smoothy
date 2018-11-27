
cmake_minimum_required (VERSION 3.12)

if (CMAKE_BUILD_TYPE STREQUAL "DebugAsm")
	enable_language(ASM)
endif()

add_library(smoothy INTERFACE)

target_include_directories(smoothy INTERFACE
	"${CMAKE_CURRENT_SOURCE_DIR}"
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/smoothy)

install(DIRECTORY . DESTINATION include/smoothy
        FILES_MATCHING PATTERN "*.h")

# in theory those are useless...
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	add_definitions(-DDEBUG)
	target_compile_options(smoothy INTERFACE -O0 -ggdb3)
elseif (CMAKE_BUILD_TYPE STREQUAL "DebugAsm")
	add_definitions(-DPRINT_ASM -DNDEBUG)
	target_compile_options(smoothy INTERFACE -O3 -d -S -masm=intel -flto -save-temps)
elseif (CMAKE_BUILD_TYPE STREQUAL "Profiling")
	add_definitions(-DNDEBUG)
	target_compile_options(smoothy INTERFACE -O3 -flto)
else (CMAKE_BUILD_TYPE STREQUAL "Release")
	add_definitions(-DNDEBUG)
	target_compile_options(smoothy INTERFACE -O3 -flto)
endif()
