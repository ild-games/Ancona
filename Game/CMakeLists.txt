add_subdirectory(Src/Mallard/GameLib)

ancona_add_target(Mallard LINK_SFML
    SRC Src/Mallard/Platforms/Desktop/main.cpp
    STATIC_LIBS ${Ancona_Libs}
    PLATFORMS DESKTOP)

#Move files to the build directory
configure_file(Config.txt ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Mallard/Config.txt @ONLY)
configure_file(save.dat ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Mallard/save.dat COPYONLY)
file(COPY Maps DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Mallard)
