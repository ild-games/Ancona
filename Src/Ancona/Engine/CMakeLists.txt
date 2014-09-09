file(GLOB_RECURSE Ancona_Engine_Code *.cpp)
file(GLOB_RECURSE Ancona_Engine_Headers *.hpp )

add_library(Ancona_Engine ${Ancona_Engine_Code} ${Ancona_Engine_Headers})
