cmake_minimum_required (VERSION 3.13)

SET(TARGET_NAME sample_helloworld)

setup_component(TARGET ${TARGET_NAME})

file(GLOB_RECURSE TARGET_HEADERS "*.h")
file(GLOB_RECURSE TARGET_SOURCES "*.cpp")

add_executable(
    ${TARGET_NAME}
    ${TARGET_HEADERS}
    ${TARGET_SOURCES}
)

target_link_libraries(${TARGET_NAME}
	PUBLIC
	Threads::Threads
	INTERFACE 
	smoothy
)

install_binary(TARGET ${TARGET_NAME} SUBFOLDER sample BINARY helloworld)
