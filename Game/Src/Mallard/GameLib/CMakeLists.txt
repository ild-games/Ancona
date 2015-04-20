file(GLOB_RECURSE Ancona_Game_Code *.cpp)
file(GLOB_RECURSE Ancona_Game_Headers *.hpp)

add_library(Ancona_Game ${Ancona_Game_Code} ${Ancona_Game_Headers})
