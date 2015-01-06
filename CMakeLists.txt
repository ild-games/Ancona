#Owner: Jeff Swenson

cmake_minimum_required(VERSION 2.8)

project(ANCONA)

option(BuildPrototypes "BuildPrototypes" ON)
option(BuildTests "BuildTests" OFF)

#TODO JPS: Fix so that it can be specified
set(Ancona_Platform Debian)

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

if(ANDROID)
    file(GLOB Android_Project_Dir BuildTools/Platform/Android/Ancona_Project/*)
    message("Android Directory:")
    message("${Android_Project_Dir}")
    file(COPY ${Android_Project_Dir} DESTINATION ${CMAKE_BINARY_DIR}/Android)
    file(INSTALL Test/Prototype/FlappyBirdTest/main.cpp DESTINATION ${CMAKE_BINARY_DIR}/Android/jni/)

    #Set the Output directories to be in the Android jni folder
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Android/jni)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Android/jni)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

    add_custom_target(Android_Build ALL DEPENDS Ancona_Game Ancona_Engine FlappyBirdLib 
        COMMAND echo Building Android App
        COMMAND ndk-build
        COMMAND android update project -p . --target android-14
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Android)
else(ANDROID)
    #Configure output directories to be something sensible
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

endif(ANDROID)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Android/jni)


#When more folders are added at the Ancona level a CMakeTest file must 
#be created and a line should be added here.
add_subdirectory(Src/Ancona/Engine)
add_subdirectory(Src/Ancona/Util)
add_subdirectory(Src/Ancona/Game)

#Libs is a variables containing a reference to all linkable libraries
set(Libs Ancona_Game Ancona_Engine Ancona_Util ${SFML_LIBS})

#Add test directory
add_subdirectory(Test)

#Build the game executable
#add_executable(ancona_game Src/Ancona/main.cpp)
#target_link_libraries(ancona_game ${Libs})

#Move files to the build directory
configure_file(Config.txt ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Config.txt COPYONLY)

