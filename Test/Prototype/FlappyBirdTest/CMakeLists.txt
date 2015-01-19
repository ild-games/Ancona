file(GLOB_RECURSE SOURCE FlappyLib/*/*.cpp)
file(GLOB_RECURSE HEADERS FlappyLib/*/*.hpp)

#ConfigTest should be changed to prototype name
set(PrototypeGameLib FlappyBirdLib)
set(PrototypeName FlappyBirdTest)

if(ANDROID)
    set(FlappyMain Platforms/Android/main.cpp)
endif(ANDROID)

if(DESKTOP)
    set(FlappyMain Platforms/Desktop/main.cpp)
endif(DESKTOP)

add_library(${PrototypeGameLib} ${SOURCE} ${HEADERS})

ancona_add_target(${PrototypeName} LINK_SFML
    SRC ${FlappyMain}
    STATIC_LIBS  FlappyBirdLib ${Ancona_Libs}
    PLATFORMS ANDROID DESKTOP
    INCLUDES ${CMAKE_CURRENT_LIST_DIR}/FlappyLib)
