IF(ANDROID)
    file(GLOB_RECURSE Ancona_System_Code Android/*.cpp)
    file(GLOB_RECURSE Ancona_System_Headers Android/*.hpp)
ELSEIF(DESKTOP)
    file(GLOB_RECURSE Ancona_System_Code Desktop/*.cpp)
    file(GLOB_RECURSE Ancona_System_Headers Desktop/*.hpp)
ENDIF()

file(GLOB Ancona_System_Generic_Code *.cpp)
file(GLOB Ancona_System_Generic_Headers *.hpp)

add_library(Ancona_System ${Ancona_System_Code} ${Ancona_System_Headers} ${Ancona_System_Generic_Code} ${Ancona_System_Generic_Headers})
