cmake_minimum_required (VERSION 2.8.11)

project(WATCHDOG_SERVICE)

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

#common part od source code
set(WATCHDOG_SERVICE_src
        main.cpp
        externals/json.hpp
        #monitObject.h
        #monitObject.cpp
        objParams.h
        objParams.cpp
)

add_executable(${PROJECT_NAME} ${WATCHDOG_SERVICE_src})



