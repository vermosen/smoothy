cmake_minimum_required (VERSION 3.13)

SET(TARGET_NAME smoothy)

setup_component(TARGET ${TARGET_NAME})

file(GLOB_RECURSE TARGET_HEADERS CONFIGURE_DEPENDS "*.h")
file(GLOB_RECURSE TARGET_SOURCES CONFIGURE_DEPENDS "*.cpp")

add_library(
    ${TARGET_NAME} INTERFACE
)

#target_link_libraries(${TARGET_NAME} 
#	PUBLIC 
#	CONAN_PKG::eigen
#	CONAN_PKG::pfr
#)

install_library(NAME ${TARGET_NAME} HEADERS ${TARGET_HEADERS})
