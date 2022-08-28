cmake_minimum_required (VERSION 2.8.11)

project(WATCHDOG_SERVICE)


#if (CMAKE_BUILD_TYPE MATCHES DEBUG)
    set(DEBUG_MODE 1)
#endif(CMAKE_BUILD_TYPE MATCHES DEBUG)

option (DEBUG_MODE "Enable debug mode" OFF)
if (DEBUG_MODE)
    MESSAGE(STATUS "Debug mode enabled")
    add_definitions(-DDEBUG_MODE)
endif(DEBUG_MODE)


if(WIN32)
    include_directories("$ENV{VCPKG_PATH}\\include")
    link_directories("$ENV{VCPKG_PATH}\\lib")
    ADD_DEFINITIONS(-DNODEFAULTLIB:msvcrt.lib)
endif(WIN32)

if(WIN32)
else(WIN32)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

endif(WIN32)

include_directories(externals)

set(WATCHDOG_SERVICE_src
        main.cpp
        monitObject.h
        monitObject.cpp
        objParams.h
        objParams.cpp
)

add_executable(${PROJECT_NAME} ${WATCHDOG_SERVICE_src})




