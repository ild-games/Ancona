file(GLOB_RECURSE Ancona_Framework_Code *.cpp)
file(GLOB_RECURSE Ancona_Framework_Headers *.hpp )

add_library(Ancona_Framework ${Ancona_Framework_Code} ${Ancona_Framework_Headers})
install(TARGETS Ancona_Framework DESTINATION lib)
