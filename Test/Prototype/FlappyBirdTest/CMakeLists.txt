file(GLOB_RECURSE SOURCE FlappyLib/*/*.cpp)
file(GLOB_RECURSE HEADERS FlappyLib/*/*.hpp)

#ConfigTest should be changed to prototype name
set(PrototypeGameLib FlappyBirdLib)
set(PrototypeName FlappyBirdTest)

if(ANDROID)
    set(FlappySrc 
        Platforms/Android/main.cpp 
        Platforms/Android/AndroidFactory.cpp 
        Platforms/Android/AndroidFactory.hpp)
endif(ANDROID)

if(DESKTOP)
    set(FlappySrc 
        Platforms/Desktop/main.cpp
        Platforms/Desktop/DesktopFactory.cpp
        Platforms/Desktop/DesktopFactory.hpp)
endif(DESKTOP)

add_library(${PrototypeGameLib} ${SOURCE} ${HEADERS})

ancona_add_target(${PrototypeName} LINK_SFML
    SRC ${FlappySrc}
    STATIC_LIBS  FlappyBirdLib ${Ancona_Libs}
    PLATFORMS ANDROID DESKTOP
    INCLUDES ${CMAKE_CURRENT_LIST_DIR}/FlappyLib)
