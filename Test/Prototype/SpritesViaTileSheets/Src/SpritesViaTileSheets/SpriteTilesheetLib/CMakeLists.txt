file(GLOB_RECURSE SpriteTilesheet_Lib_Code *.cpp)
file(GLOB_RECURSE SpriteTilesheet_Lib_Headers *.hpp)

add_library(SpriteTilesheet_Lib ${SpriteTilesheet_Lib_Code} ${SpriteTilesheet_Lib_Headers})
