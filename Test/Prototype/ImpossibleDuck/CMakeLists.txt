#ConfigTest should be changed to prototype name
set(PrototypeGameLib Impossible_Lib)
set(PrototypeName ImpossibleDuckTest)

add_subdirectory(Src/ImpossibleDuck/ImpossibleLib)

if(ANDROID)
    set(ImpossibleSrc Src/ImpossibleDuck/Platforms/Android/main.cpp)
endif(ANDROID)

if(DESKTOP)
    set(ImpossibleSrc Src/ImpossibleDuck/Platforms/Desktop/main.cpp)
endif(DESKTOP)

ancona_add_target(ImpossibleDuckProto LINK_SFML
    SRC ${ImpossibleSrc}
    STATIC_LIBS  Impossible_Lib ${Ancona_Libs}
    PLATFORMS ANDROID DESKTOP
    INCLUDES ${CMAKE_CURRENT_LIST_DIR}/ImpossibleLib)

configure_file(Config.txt ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ImpossibleDuckProto/Config.txt @ONLY)
configure_file(save.dat ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ImpossibleDuckProto/save.dat COPYONLY)
file(COPY Maps DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ImpossibleDuckProto)
