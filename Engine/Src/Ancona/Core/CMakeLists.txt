file(GLOB_RECURSE Ancona_Core_Code *.cpp)
file(GLOB_RECURSE Ancona_Core_Headers *.hpp *.inl)

add_library(Ancona_Core ${Ancona_Core_Code} ${Ancona_Core_Headers})
install(TARGETS Ancona_Core DESTINATION lib)
