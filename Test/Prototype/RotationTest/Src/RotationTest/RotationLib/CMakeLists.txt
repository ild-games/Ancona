file(GLOB_RECURSE Rotation_Lib_Code *.cpp)
file(GLOB_RECURSE Rotation_Lib_Headers *.hpp)

add_library(Rotation_Lib ${Rotation_Lib_Code} ${Rotation_Lib_Headers})
