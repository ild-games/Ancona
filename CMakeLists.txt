#Owner: Jeff Swenson

cmake_minimum_required(VERSION 2.8)

project(ANCONA)

include (${RAFT})

option(BuildPrototypes "BuildPrototypes" ON)
option(BuildTests "BuildTests" ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/BuildTools/Modules)

#Set C++ Version to 11
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall")

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" AND NOT ANDROID)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
endif()

include_directories(Engine/Src)

set(ANCONA_LIBS Ancona_Platformer Ancona_Core2D
    Ancona_Framework Ancona_Util2D Ancona_Util Ancona_System)

set(ANCONA_EXT_LIBS sfml-graphics sfml-window sfml-system jsoncpp)

if(ANDROID)
    set(ANCONA_EXT_LIBS ${ANCONA_EXT_LIBS} android EGL log)
    set(ANCONA_WHOLE_EXT_LIBS sfml-main)
endif()

#Configure output directories to be something sensible
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(Engine)
add_subdirectory(Test)
