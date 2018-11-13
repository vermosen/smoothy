
cmake_minimum_required (VERSION 3.12)

add_library(smoothy INTERFACE)

target_include_directories(smoothy INTERFACE
	"${CMAKE_CURRENT_SOURCE_DIR}"
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/smoothy)

install(DIRECTORY . DESTINATION include/smoothy
        FILES_MATCHING PATTERN "*.h")
