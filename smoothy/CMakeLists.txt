# CMakeList.txt : CMake project for smoothy, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.12)

# set debug target
if (CMAKE_CONF MATCHES "Debug")
	set(CMAKE_BUILD_TYPE Debug)
endif (CMAKE_CONF MATCHES "Debug")

file(GLOB_RECURSE SMOOTHY_FILES "*.h" "*.cpp")

set(QL_LINK_LIBRARY ${SMOOTHY_OUTPUT_NAME} PARENT_SCOPE)

install(DIRECTORY . DESTINATION include/smoothy
        FILES_MATCHING PATTERN "*.h")

install(TARGETS ${SMOOTHY_OUTPUT_NAME}
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
        )
