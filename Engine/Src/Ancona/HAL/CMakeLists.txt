IF("${ANCONA_HAL_ID}" STREQUAL "SDL")
    file(GLOB_RECURSE Ancona_HAL_Code SDL/*.cpp)
    file(GLOB_RECURSE Ancona_HAL_Headers SDL/*.hpp)
ELSEIF("${ANCONA_HAL_ID}" STREQUAL "SFML")
    file(GLOB_RECURSE Ancona_HAL_Code SFML/*.cpp)
    file(GLOB_RECURSE Ancona_HAL_Headers SFML/*.hpp)
ELSE() # Default HAL layer to SFML
    file(GLOB_RECURSE Ancona_HAL_Code SFML/*.cpp)
    file(GLOB_RECURSE Ancona_HAL_Headers SFML/*.hpp)
ENDIF()

file(GLOB Ancona_HAL_Generic_Code *.cpp)
file(GLOB Ancona_HAL_Generic_Headers *.hpp)

add_library(Ancona_HAL ${Ancona_HAL_Code} ${Ancona_HAL_Headers} ${Ancona_HAL_Generic_Code} ${Ancona_HAL_Generic_Headers})
install(TARGETS Ancona_HAL DESTINATION lib)
