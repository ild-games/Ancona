file(GLOB_RECURSE SOURCE JumpyLib/*/*.cpp)
file(GLOB_RECURSE HEADERS JumpyLib/*/*.hpp)

#ConfigTest should be changed to prototype name
set(PrototypeGameLib JumpyDuckLib)
set(PrototypeName JumpyDuckTest)


set(JumpySrc Platforms/Desktop/main.cpp)

add_library(${PrototypeGameLib} ${SOURCE} ${HEADERS})

ancona_add_target(${PrototypeName} LINK_SFML
    SRC ${JumpySrc}
    STATIC_LIBS  ${PrototypeGameLib} ${Ancona_Libs}
    PLATFORMS DESKTOP
    INCLUDES ${CMAKE_CURRENT_LIST_DIR}/JumpyLib)
