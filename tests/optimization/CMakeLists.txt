cmake_minimum_required (VERSION 3.13)

SET(TARGET_NAME test_optimization)
setup_component(TARGET ${TARGET_NAME})

file(GLOB_RECURSE TARGET_HEADERS "*.h")
file(GLOB_RECURSE TARGET_SOURCES "*.cpp")

add_executable(
    ${TARGET_NAME}
    ${TARGET_HEADERS}
    ${TARGET_SOURCES}
)

gtest_add_tests(
	TARGET ${TARGET_NAME}
)

target_link_libraries(${TARGET_NAME}
	INTERFACE 
	smoothy
	PUBLIC
	CONAN_PKG::gtest
	Threads::Threads
)
