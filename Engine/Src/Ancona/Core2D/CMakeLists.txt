file(GLOB_RECURSE Ancona_Core2D_Code *.cpp)
file(GLOB_RECURSE Ancona_Core2D_Headers *.hpp *.inl)

add_library(Ancona_Core2D ${Ancona_Core2D_Code} ${Ancona_Core2D_Headers})
install(TARGETS Ancona_Core2D DESTINATION lib)
