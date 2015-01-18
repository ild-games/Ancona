#Owner: Jeff Swenson

cmake_minimum_required(VERSION 2.8)

project(ANCONA)

include(BuildTools/Macros.cmake)

option(BuildPrototypes "BuildPrototypes" ON)
option(BuildTests "BuildTests" OFF)

# Set variables to indicate the build platform
# There will be one platform variable defined and one form factor variable defined
# 
# Platform Variables: ANDROID, DEBIAN, OSX, WINDOWS
# Form Factor Variables: MOBILE, DESKTOP
if(ANDROID)
    message("Configuring for Android")
    set(MOBILE True)
endif(ANDROID)
if(NOT ANDROID)
    if(CMAKE_HOST_APPLE)
        message("Configuring for OSX")
        set(OSX True)
        set(DESKTOP True)
    endif(CMAKE_HOST_APPLE)
    if(CMAKE_HOST_WIN32)
        message("Configuring for Windows")
        set(WINDOWS True)
        set(DESKTOP True)
    endif(CMAKE_HOST_WIN32)
    if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
        message("Configuring for Debian")
        set(DEBIAN True)
        set(DESKTOP True)
    endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
endif(NOT ANDROID)

set(CMAKE_MODULE_PATH BuildTools/Module ${CMAKE_MODULE_PATH})

#Set C++ Version to 11
SET(CMAKE_CXX_FLAGS "-std=c++11 -g -lstdc++")

#Define SRC_DIR and INC_DIR incase we choose to separate
#cpp and hpp files in the future
set(SRC_DIR ${CMAKE_SOURCE_DIR}/Src/Ancona)
set(INC_DIR ${CMAKE_SOURCE_DIR}/Src/Ancona)

include(BuildTools/FindLibs.cmake)
#Add all SFML libraries that need to be included
set(SFML_LIBS sfml-graphics sfml-window sfml-system)

#Incldue directory over the INC_DIR variable.  This is done so that
#project headers are prefaced with Ancona
include_directories(${INC_DIR}/..)

#Configure output directories to be something sensible
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#When more folders are added at the Ancona level a CMakeTest file must 
#be created and a line should be added here.
add_subdirectory(Src/Ancona/Engine)
add_subdirectory(Src/Ancona/Util)
add_subdirectory(Src/Ancona/Game)

#Libs is a variables containing a reference to all linkable libraries
set(Libs Ancona_Game Ancona_Engine Ancona_Util ${SFML_LIBS})
set(Ancona_Libs Ancona_Game Ancona_Engine Ancona_Util)

#Add test directory
add_subdirectory(Test)

#Build the game executable
ancona_add_target(ancona_game LINK_SFML
    SRC Src/Ancona/main.cpp
    STATIC_LIBS ${Ancona_Libs}
    PLATFORMS ALL)

#Move files to the build directory
configure_file(Config.txt ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Config.txt COPYONLY)
