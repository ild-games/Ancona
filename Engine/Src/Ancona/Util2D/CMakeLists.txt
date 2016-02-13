file(GLOB_RECURSE Ancona_Util2D_Code *.cpp)
file(GLOB_RECURSE Ancona_Util2D_Headers *.hpp)

add_library(Ancona_Util2D ${Ancona_Util2D_Code} ${Ancona_Util2D_Headers})
install(TARGETS Ancona_Util2D DESTINATION lib)
