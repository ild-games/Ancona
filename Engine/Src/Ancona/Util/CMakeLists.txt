file(GLOB_RECURSE Ancona_Util_Code *.cpp)
file(GLOB_RECURSE Ancona_Util_Headers *.hpp)

add_library(Ancona_Util ${Ancona_Util_Code} ${Ancona_Util_Headers})
install(TARGETS Ancona_Util DESTINATION lib)
