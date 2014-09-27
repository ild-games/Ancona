file(GLOB_RECURSE Ancona_Game_Code *.cpp)
file(GLOB_RECURSE Ancona_Game_Headers *.hpp)

set(Libs Ancona_Engine Ancona_Util ${SFML_LIBS})

add_executable(ancona_game ${Ancona_Game_Code} ${Ancona_Game_Headers})
target_link_libraries(ancona_game ${Libs})

configure_file(Config.txt ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Config.txt COPYONLY)
configure_file(TestRequestList.txt ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/TestRequestList.txt COPYONLY)
