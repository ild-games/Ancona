include(CMakeParseArguments)

MACRO(LIST_CONTAINS var value)
  SET(${var})
  FOREACH (value2 ${ARGN})
    IF (${value} STREQUAL ${value2})
      SET(${var} TRUE)
    ENDIF (${value} STREQUAL ${value2})
  ENDFOREACH (value2)
ENDMACRO(LIST_CONTAINS)

macro(ancona_match_platform result)
    set(${result} FALSE)
    LIST_CONTAINS(has_android_platform ANDROID ${ARGN})
    LIST_CONTAINS(has_ios_platform IOS ${ARGN})
    LIST_CONTAINS(has_mobile_platform MOBILE ${ARGN})

    LIST_CONTAINS(has_debian_platform DEBIAN ${ARGN})
    LIST_CONTAINS(has_osx_platform OSX ${ARGN})
    LIST_CONTAINS(has_windows_platform WINDOWS ${ARGN})
    LIST_CONTAINS(has_desktop_platform DESKTOP ${ARGN})

    LIST_CONTAINS(has_all_platform ALL ${ARGN})

    if(ANDROID AND has_android_platform)
        set(${result} TRUE)
    endif(ANDROID AND has_android_platform)

    if(IOS AND has_ios_platform)
        set(${result} TRUE)
    endif(IOS AND has_ios_platform)

    if((IOS OR ANDROID) AND has_mobile_platform)
        set(${result} TRUE)
    endif((IOS OR ANDROID) AND has_mobile_platform)

    if(DEBIAN AND has_debian_platform)
        set(${result} TRUE)
    endif(DEBIAN AND has_debian_platform)

    if(OSX AND has_osx_platform)
        set(${result} TRUE)
    endif(OSX AND has_osx_platform)

    if(WINDOWS AND has_windows_platform)
        set(${result} TRUE)
    endif(WINDOWS AND has_windows_platform)

    if((DEBIAN OR OSX OR WINDOWS) AND has_desktop_platform)
        set(${result} TRUE)
    endif((DEBIAN OR OSX OR WINDOWS) AND has_desktop_platform)

    if(has_all_platform)
        set(${result} TRUE)
    endif()
endmacro()

macro(ancona_platform_glob)
    cmake_parse_arguments(ARGS "" "" "" ${ARGN})
endmacro()

# ex: ancona_add_target(flappy_demo
# SRC main.cpp ...
# STATIC_LIBS Ancona_Util Ancona_Game Flapp_Game
# INCLUDES /Abs/Paths/To/Add/To/Includes
# PLATFORMS ALL)
macro(ancona_add_target target)
    cmake_parse_arguments(ARGS "" "" "SRC;STATIC_PROJECT_LIBS;DYNAMIC_PROJECT_LIBS;STATIC_DEPEND_LIBS;DYNAMIC_DEPEND_LIBS;PLATFORMS;INCLUDES" ${ARGN})

    ancona_match_platform(is_platform_match ${ARGS_PLATFORMS})

    if(is_platform_match)
        if(DESKTOP)
            set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${target})
            add_executable(${target} ${ARGS_SRC})
            set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

            #Add custom includes
            if(ARGS_INCLUDES)
                target_include_directories(${target} PUBLIC ${ARGS_INCLUDES})
            endif(ARGS_INCLUDES)

            target_link_libraries(${target} ${ARGS_STATIC_PROJECT_LIBS} ${ARGS_DYNAMIC_PROJECT_LIBS} 
                ${ARGS_STATIC_DYNAMIC_LIBS} ${ARGS_DYNAMIC_DEPEND_LIBS})
            
        endif(DESKTOP)

        if(ANDROID)
            #Copy files over
            file(GLOB Android_Project_Dir ${CMAKE_SOURCE_DIR}/BuildTools/Platform/Android/Ancona_Project/*)
            file(GLOB Android_Assets ${CMAKE_SOURCE_DIR}/resources/*)

            file(COPY ${Android_Project_Dir} DESTINATION ${CMAKE_BINARY_DIR}/Android/${target})
            file(COPY ${Android_Assets} DESTINATION ${CMAKE_BINARY_DIR}/Android/${target}/assets/resources)
            file(COPY ${ARGS_SRC} DESTINATION ${CMAKE_BINARY_DIR}/Android/${target}/jni/)

            add_library(${target} SHARED ${ARGS_SRC})

            #Add custom includes
            if(ARGS_INCLUDES)
                target_include_directories(${target} PUBLIC ${ARGS_INCLUDES})
            endif(ARGS_INCLUDES)

            target_link_libraries(${target} ${ARGS_STATIC_PROJECT_LIBS} ${ARGS_DYNAMIC_PROJECT_LIBS} 
                ${ARGS_STATIC_DEPEND_LIBS} ${ARGS_DYNAMIC_DEPEND_LIBS})
        endif(ANDROID)
    endif(is_platform_match)

endmacro()

# runs add_subdirectory for all directories in current directory
# ex: SUBDIRLIST(SUBDIRS ${MY_CURRENT_DIR})
MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
        LIST(APPEND dirlist ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()
