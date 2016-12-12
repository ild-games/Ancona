file(GLOB_RECURSE Ancona_Menu_Code *.cpp)
file(GLOB_RECURSE Ancona_Menu_Headers *.hpp)

add_library(Ancona_Menu ${Ancona_Menu_Code} ${Ancona_Menu_Headers})
install(TARGETS Ancona_Menu DESTINATION lib)
