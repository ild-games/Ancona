file(GLOB_RECURSE Jumpy_Lib_Code *.cpp)
file(GLOB_RECURSE Jumpy_Lib_Headers *.hpp)

add_library(Jumpy_Lib ${Jumpy_Lib_Code} ${Jumpy_Lib_Headers})
