set(PrototypeGameLib SpriteTilesheet_Lib)
set(PrototypeName SpritesViaTileSheets)

add_subdirectory(Src/SpritesViaTileSheets/SpriteTilesheetLib)

if(ANDROID)
    set(SpriteTilesheetSrc Src/SpritesViaTileSheets/Platforms/Android/main.cpp)
endif(ANDROID)

if(DESKTOP)
    set(SpriteTilesheetSrc Src/SpritesViaTileSheets/Platforms/Desktop/main.cpp)
endif(DESKTOP)

ancona_add_target(SpritesViaTileSheets LINK_SFML
    SRC ${SpriteTilesheetSrc}
    STATIC_LIBS SpriteTilesheet_Lib ${Ancona_Libs}
    PLATFORMS ANDROID DESKTOP
    INCLUDES ${CMAKE_CURRENT_LIST_DIR}/SpriteTilesheetLib)

configure_file(Config.txt ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SpritesViaTileSheets/Config.txt @ONLY)
configure_file(save.dat ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SpritesViaTileSheets/save.dat COPYONLY)
file(COPY Maps DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SpritesViaTileSheets)
