#Owner: Jeff Swenson

cmake_minimum_required(VERSION 2.8)

project(ANCONA)

option(BuildPrototypes "BuildPrototypes" ON)

#Set C++ Version to 11
SET(CMAKE_CXX_FLAGS "-std=c++11 -g -lstdc++")

#Define SRC_DIR and INC_DIR incase we choose to separate
#cpp and hpp files in the future
set(SRC_DIR ${CMAKE_SOURCE_DIR}/Src/Ancona)
set(INC_DIR ${CMAKE_SOURCE_DIR}/Src/Ancona)

#Configure output directories to be something sensible
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#Add all SFML libraries that need to be included
set(SFML_LIBS sfml-graphics sfml-window sfml-system)

#Incldue directory over the INC_DIR variable.  This is done so that
#project headers are prefaced with Ancona
include_directories(${INC_DIR}/..)

#When more folders are added at the Ancona level a CMakeTest file must 
#be created and a line should be added here.
add_subdirectory(Src/Ancona/Engine)
add_subdirectory(Src/Ancona/Game)
add_subdirectory(Src/Ancona/Util)

if(BuildPrototypes)
    add_subdirectory(Test/Prototype)
endif(BuildPrototypes)
