#Owner: Jeff Swenson

cmake_minimum_required(VERSION 2.8)

project(ANCONA)

include(BuildTools/Macros.cmake)

option(BuildPrototypes "BuildPrototypes" ON)
option(BuildTests "BuildTests" ON)

set(PLATFORM_NAME "system" CACHE STRING "[ system android ]")
set(ARCHITECTURE_NAME "system" CACHE STRING "[ system x64 x86 armeabi ]")

set(EXT_PLAT_DIR ${CMAKE_SOURCE_DIR}/extlibs/lib/${PLATFORM_NAME})
set(EXT_LIB_DIR ${EXT_PLAT_DIR}/${ARCHITECTURE_NAME})
set(EXT_INCLUDE ${CMAKE_SOURCE_DIR}/extlibs/include)

# Set variables to indicate the build platform
# There will be one platform variable defined and one form factor variable defined
# 
# Platform Variables: ANDROID, DEBIAN, OSX, WINDOWS
# Form Factor Variables: MOBILE, DESKTOP
#
# Ancona_Platform will be set to the name of the set platform variable.
# Ancona_FormFactor will be set to the name of the set formfactor.
if(ANDROID)
    message("Configuring for Android")
    set(Ancona_Platform ANDROID)
    set(Ancona_Form_Factor MOBILE)
endif(ANDROID)
if(NOT ANDROID)
    if(CMAKE_HOST_APPLE)
        message("Configuring for OSX")
        set(Ancona_Platform OSX)
        set(Ancona_Form_Factor DESKTOP)
    endif(CMAKE_HOST_APPLE)
    if(CMAKE_HOST_WIN32)
        message("Configuring for Windows")
        set(Ancona_Platform WINDOWS)
        set(Ancona_Form_Factor DESKTOP)
    endif(CMAKE_HOST_WIN32)
    if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
        message("Configuring for Debian")
        set(Ancona_Platform DEBIAN)
        set(Ancona_Form_Factor DESKTOP)
    endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
endif(NOT ANDROID)

set(${Ancona_Platform} True)
set(${Ancona_Form_Factor} True)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/BuildTools/Modules)

#Set C++ Version to 11
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall")

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" AND NOT ANDROID)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
endif()

include_directories(${EXT_INCLUDE} Game/Src Engine/Src)
link_directories(${EXT_LIB_DIR})

include(BuildTools/FindLibs.cmake)

set(ANCONA_LIBS Ancona_Game Ancona_Platformer Ancona_Core2D 
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
add_subdirectory(Game)
add_subdirectory(Test)
