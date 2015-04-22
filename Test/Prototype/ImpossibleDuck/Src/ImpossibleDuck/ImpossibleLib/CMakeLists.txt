file(GLOB_RECURSE Impossible_Lib_Code *.cpp)
file(GLOB_RECURSE Impossible_Lib_Headers *.hpp)

add_library(Impossible_Lib ${Impossible_Lib_Code} ${Impossible_Lib_Headers})
