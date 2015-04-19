add_subdirectory(Src/QJack)

ancona_add_target(QJack LINK_SFML
    SRC Src/Platforms/Desktop/main.cpp
    STATIC_LIBS ${Ancona_Libs}
    PLATFORMS ALL)

#Move files to the build directory
configure_file(Config.txt ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/QJack/Config.txt @ONLY)
configure_file(save.dat ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/QJack/save.dat COPYONLY)
file(COPY Maps DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/QJack)
