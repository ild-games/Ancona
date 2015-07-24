#ConfigTest should be changed to prototype name
set(PrototypeGameLib Jumpy_Lib)
set(PrototypeName JumpyDuckTest)

add_subdirectory(Src/JumpyDuck/JumpyLib)

set(JumpySrc Src/JumpyDuck/Platforms/Desktop/main.cpp)

ancona_add_target(JumpyDuckProto
    SRC ${JumpySrc}
    LIBS Jumpy_Lib ${ANCONA_LIBS} ${ANCONA_EXT_LIBS}
    WHOLE_STATIC_LIBS ${ANCONA_WHOLE_EXT_LIBS}
    PLATFORMS DESKTOP)

configure_file(Config.txt ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/JumpyDuckProto/Config.txt @ONLY)
configure_file(save.dat ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/JumpyDuckProto/save.dat COPYONLY)
file(COPY Maps DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/JumpyDuckProto)
