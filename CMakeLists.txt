cmake_minimum_required(VERSION 3.22.0)
#Owner: Jeff Swenson

project(ANCONA)

include (${RAFT})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/BuildTools/Modules)

#Set C++ Version to C++14
set(CMAKE_CXX_STANDARD 14)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" AND NOT ANDROID AND NOT IOS AND NOT WIN32)
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

set (ANCONA_HAL_ID "SDL")

include_directories(Engine/Src)


set (ANCONA_LIBS
    Ancona_Core
    Ancona_Core2D
    Ancona_Framework
    Ancona_Graphics
    Ancona_HAL
    Ancona_Menu
    Ancona_Platformer
    Ancona_System
    Ancona_Util
    Ancona_Util2D)

set(ANCONA_EXT_LIBS
    optimized sfml-graphics debug sfml-graphics-d
    optimized sfml-window debug sfml-window-d
    optimized sfml-system debug sfml-system-d
    SDL2
    SDL2_image)

if(ANDROID)
    set(ANCONA_EXT_LIBS ${ANCONA_EXT_LIBS} android EGL log)
    set(ANCONA_WHOLE_EXT_LIBS sfml-main)
endif()

#Configure output directories to be something sensible
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# forward the SDL2 include directory so SDL_Image includes work
include_directories("${RAFT_INCLUDE_DIR}/SDL2")

add_subdirectory(Engine)
