#When more folders are added at the Ancona level a CMakeTest file must
#be created and a line should be added here.
add_subdirectory(Src/Ancona/Core2D)
add_subdirectory(Src/Ancona/Framework)
add_subdirectory(Src/Ancona/HAL)
add_subdirectory(Src/Ancona/Platformer)
add_subdirectory(Src/Ancona/Util)
add_subdirectory(Src/Ancona/Util2D)
add_subdirectory(Src/Ancona/Menu)
add_subdirectory(Src/Ancona/System)

install(DIRECTORY Src/ DESTINATION include
    FILES_MATCHING PATTERN *.hpp PATTERN *.inl)
