
cmake_minimum_required (VERSION 3.12 FATAL_ERROR)

include_guard(GLOBAL)


message(STATUS   "\n")
message(STATUS   ":================:")
message(STATUS   ":setting up conan:")
message(STATUS   ":================:\n")

# conan setup
set(CONAN_USER		"rubedo"										)
set(CONAN_CHANNEL	"stable"										)
set(CONAN_SERVER	"hap-server"									)
set(CONAN_URL		http://conan-server.build.marathon.mesos:9300	)

message(STATUS "adding conan remote \"${CONAN_SERVER}\" at ${CONAN_URL}")
message(STATUS "conan channel set to ${CONAN_USER}/${CONAN_CHANNEL}")

if (EXISTS "$ENV{HOME}/.cmake/conan.cmake")
	include("$ENV{HOME}/.cmake/conan.cmake")
else()
	message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan into $ENV{HOME}/.cmake")
	file(
		DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
		"$ENV{HOME}/.cmake/conan.cmake"
	)
	if (NOT EXISTS "$ENV{HOME}/.cmake/conan.cmake")
		message(FATAL_ERROR "cannot load conan description from github, aborting..." )
	else()
		message(STATUS "conan description file has been installed in $ENV{HOME}/.cmake")
	endif()
endif()

# expected location of the conan.cmake file
include($ENV{HOME}/.cmake/conan.cmake)

conan_check(VERSION 1.9.2 REQUIRED)

conan_add_remote(
	NAME	${CONAN_SERVER}
	URL		${CONAN_URL}
)

macro(import_packages)

	set(REPOS "")
	foreach(PKG ${ARGN})
		import_pkg(${PKG})
	endforeach(PKG)

	MESSAGE(STATUS "repos to be loaded: ${REPOS}")

	MESSAGE(STATUS "loading: ${CMAKE_BUILD_TYPE}")

	conan_cmake_run(
		REQUIRES ${REPOS}
		BASIC_SETUP CMAKE_TARGETS
		BASIC_SETUP KEEP_RPATHS
		BUILD missing
		BUILD_TYPE ${CMAKE_BUILD_TYPE}
	)

	# set the global project flags (same as removing the CMAKE_TARGETS above)
	conan_global_flags()

	foreach(PKG ${ARGN})
		string(TOUPPER ${PKG} UCASE)
		if(${UCASE}_CMAKE_CONFIG)
			MESSAGE(STATUS "${UCASE}_CMAKE_CONFIG has been defined. Looking for ${PKG}Config.cmake...")
			find_package(${PKG})
			if (${${PKG}_FOUND})
				MESSAGE(STATUS "${PKG} package ... Found")
			else()
				MESSAGE(FATAL_ERROR "${PKG} package ... Not Found !")
			endif()
		endif()
	endforeach(PKG)
endmacro()

macro(import_pkg libname)

	string(TOUPPER ${libname} UCASE)
	log_debug("${libname} tag set to ${UCASE}")
	get_property(tmp GLOBAL PROPERTY CONAN_FOUNDLIB_${UCASE})
	if(tmp)
		log_debug("${libname} already imported, skipping...")
	else()

		# optional: allows override of the channel used
		# through variables FOOBAR_CONAN_CHANNEL_OVERRIDE
		if (DEFINED ${UCASE}_CONAN_CHANNEL_OVERRIDE)
			MESSAGE(WARNING "${libname} channel has been overriden to ${${UCASE}_CONAN_CHANNEL_OVERRIDE}")
			set(${UCASE}_CONAN_CHANNEL ${${UCASE}_CONAN_CHANNEL_OVERRIDE})
		else()
			set(${UCASE}_CONAN_CHANNEL ${CONAN_CHANNEL})
		endif()

		list(APPEND REPOS "${libname}/${${UCASE}_VERS}@${CONAN_USER}/${${UCASE}_CONAN_CHANNEL}")
		set(tmp ON)
		log_debug("${libname} found, setting variable CONAN_FOUNDLIB_${UCASE} to ${tmp}")
	endif()
	set_property(GLOBAL PROPERTY CONAN_FOUNDLIB_${UCASE} tmp)
endmacro()
