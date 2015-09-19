file(GLOB_RECURSE Ghosted_Lib_Code *.cpp)
file(GLOB_RECURSE Ghosted_Lib_Headers *.hpp)

add_library(Ghosted_Lib ${Ghosted_Lib_Code} ${Ghosted_Lib_Headers})
