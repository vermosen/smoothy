
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
	target_compile_options(smoothy INTERFACE -O0 -ggdb3 -DDEBUG)
elseif (CMAKE_BUILD_TYPE STREQUAL "DebugAsm")
	target_compile_options(smoothy INTERFACE -O3 -DNDEBUG -flto -S -masm=intel -DDEBUG_ASM -save-temps)
elseif (CMAKE_BUILD_TYPE STREQUAL "Profiling")
	target_compile_options(smoothy INTERFACE -O3 -DNDEBUG -flto)
else (CMAKE_BUILD_TYPE STREQUAL "Release")
	target_compile_options(smoothy INTERFACE -O3 -DNDEBUG -flto)
endif()
