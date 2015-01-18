file(GLOB_RECURSE SOURCE */*.cpp)
file(GLOB_RECURSE HEADERS */*.hpp)

#ConfigTest should be changed to prototype name
set(PrototypeGameLib FlappyBirdLib)
set(PrototypeName FlappyBirdTest)

add_library(${PrototypeGameLib} ${SOURCE} ${HEADERS})
ancona_add_target(${PrototypeName} LINK_SFML
    SRC main.cpp
    STATIC_LIBS  FlappyBirdLib ${Ancona_Libs}
    PLATFORMS ANDROID DESKTOP
    INCLUDES ${CMAKE_CURRENT_LIST_DIR})
