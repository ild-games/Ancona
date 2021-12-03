file(GLOB_RECURSE Ancona_Graphics_Code *.cpp)
file(GLOB_RECURSE Ancona_Graphics_Headers *.hpp *.inl)

add_library(Ancona_Graphics ${Ancona_Graphics_Code} ${Ancona_Graphics_Headers})
install(TARGETS Ancona_Graphics DESTINATION lib)
