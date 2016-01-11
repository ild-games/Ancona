file(GLOB_RECURSE Ancona_Platformer_Code *.cpp)
file(GLOB_RECURSE Ancona_Platformer_Headers *.hpp)

add_library(Ancona_Platformer ${Ancona_Platformer_Code} ${Ancona_Platformer_Headers})
install(TARGETS Ancona_Platformer DESTINATION lib)
