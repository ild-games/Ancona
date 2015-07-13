IF(ANDROID)
    set(Src Android/Platform.cpp)
ELSEIF(DESKTOP)
    set(Src Desktop/Platform.cpp)
ENDIF()

add_library(Ancona_System ${Src})
