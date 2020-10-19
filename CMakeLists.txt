cmake_minimum_required (VERSION 3.13)

option(SKIP_CONAN_PACKAGE "skip conan package generation" OFF)

set(PROJECT_HOME "${CMAKE_CURRENT_LIST_DIR}")
set(PROJECT_NAME smoothy CACHE STRING "" FORCE)
set(PROJECT_NAMESPACE smoothy CACHE STRING "" FORCE)
string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_U)

message(STATUS "*** variable PROJECT_NAME set to: ${PROJECT_NAME} ***")
message(STATUS "*** variable PROJECT_NAMESPACE set to: ${PROJECT_NAMESPACE} ***")
message(STATUS "*** variable PROJECT_HOME set to: ${PROJECT_HOME} ***")

##############################
#      include toolsets      #
##############################

message(STATUS "*** retrieving cmake configuration from ${PROJECT_HOME}/cmake ***")

include("${PROJECT_HOME}/cmake/CMakeLists.txt")

###########################
#  defines cmake project  #
###########################

set(${PROJECT_NAME_U}_MAJOR_VERSION 0)
set(${PROJECT_NAME_U}_MINOR_VERSION 1)
set(${PROJECT_NAME_U}_BUILD_VERSION 1)

set(${PROJECT_NAME_U}_VERSION
  ${${PROJECT_NAME_U}_MAJOR_VERSION}.${${PROJECT_NAME_U}_MINOR_VERSION}.${${PROJECT_NAME_U}_BUILD_VERSION})

message(STATUS "project version set to ${${PROJECT_NAME_U}_VERSION}")

project(
	${PROJECT_NAME}
	LANGUAGES C CXX CUDA
	VERSION	${${PROJECT_NAME_U}_VERSION}
	DESCRIPTION "the smoothy library"
)

##############################
# import thirdparty packages #
##############################

set(EIGEN_VERS    "3.3.7" )
set(BOOST_VERS    "1.72.0")
set(PFR_VERS      "1.0.0" )
set(META_VERS     "0.1.5" )
set(GTEST_VERS    "1.8.1" )

set(PACKAGES 
	eigen boost
	meta gtest pfr
)

message(STATUS "package list has been set to ${PACKAGES}")

# imported packages
load_packages(
	NAME ${PACKAGES}
	PROFILE ${CONAN_PROFILE}
	SETTINGS ${CONAN_EXTRA_SETTINGS}
	UPDATE
)

create_debug_conf(NAME ${PACKAGES})

message(DEBUG "CONAN_LIBS set to ${CONAN_LIBS}")

#####################################
#          generate exports         #
#####################################

export_project(
	NAME ${PROJECT_NAME}
	NAMESPACE ${PROJECT_NAME}
	REVISION ${${PROJECT_NAME_U}_VERSION}
	DIRECTORY cmake/package # for later use
)

if (SKIP_CONAN_PACKAGE STREQUAL "OFF")

	conan_export(
		PACKAGE ${PROJECT_NAME}
		REVISION ${${PROJECT_NAME_U}_VERSION}
		USER ${CONAN_USER}
		CHANNEL ${CONAN_CHANNEL}
		PROFILE ${CONAN_PROFILE}
		DIRECTORY conan
	)

endif()

#####################################
#          add the sources          #
#####################################

include_directories(src)

#####################################
#     add the project libraries     #
#####################################

add_subdirectory(src/smoothy)

#####################################
#    add the project applications   #
#####################################

add_subdirectory(sample)

#####################################
#             ctest setup           #
#####################################

include(CTest)
add_subdirectory(tests)