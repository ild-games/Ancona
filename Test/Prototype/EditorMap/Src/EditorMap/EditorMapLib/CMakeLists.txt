file(GLOB_RECURSE EditorMap_Lib_Code *.cpp)
file(GLOB_RECURSE EditorMap_Lib_Headers *.hpp)

add_library(EditorMap_Lib ${EditorMap_Lib_Code} ${EditorMap_Lib_Headers})
