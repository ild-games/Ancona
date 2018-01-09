#Owner: Jeff Swenson

cmake_minimum_required(VERSION 2.8)

project(ANCONA)

include (${RAFT})

option(BuildPrototypes "BuildPrototypes" ON)
option(BuildTests "BuildTests" ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/BuildTools/Modules)

#Set C++ Version to 11
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" AND NOT ANDROID AND NOT IOS)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address")
endif()
if(IOS)
    set(CMAKE_XX_FLAG "-x objective-c++")
    set(CMAKE_OSX_SYSROOT iphoneos)
    if (RAFT_ARCH) 
        set(CMAKE_OSX_ARCHITECTURES RAFT_ARCH)
    else()
        set(CMAKE_OSX_ARCHITECTURES $(ARCHS_STANDARD_32_BIT))
    endif()
    set(CMAKE_XCODE_EFFECTIVE_PLATFORMS "-iphoneos;-iphonesimulator")
endif()

include_directories(Engine/Src)

set(ANCONA_LIBS Ancona_Platformer Ancona_Core2D
    Ancona_Framework Ancona_Util2D Ancona_Util Ancona_System)


set(ANCONA_EXT_LIBS
    optimized sfml-graphics debug sfml-graphics-d
    optimized sfml-window debug sfml-window-d
    optimized sfml-system debug sfml-system-d)

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
