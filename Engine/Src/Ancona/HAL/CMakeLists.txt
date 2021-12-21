IF("${ANCONA_HAL_ID}" STREQUAL "SDL")
    file(GLOB_RECURSE Ancona_HAL_Code SDL/*.cpp)
    file(GLOB_RECURSE Ancona_HAL_Headers SDL/*.hpp SDL/*.inl)
ELSEIF("${ANCONA_HAL_ID}" STREQUAL "SFML")
    file(GLOB_RECURSE Ancona_HAL_Code SFML/*.cpp)
    file(GLOB_RECURSE Ancona_HAL_Headers SFML/*.hpp SFML/*.inl)
ELSE() # Default HAL layer to SFML
    file(GLOB_RECURSE Ancona_HAL_Code SFML/*.cpp)
    file(GLOB_RECURSE Ancona_HAL_Headers SFML/*.hpp SFML/*.inl)
ENDIF()

file(GLOB Ancona_HAL_Generic_Code *.cpp)
file(GLOB Ancona_HAL_Generic_Headers *.hpp *.inl)

add_library(Ancona_HAL ${Ancona_HAL_Code} ${Ancona_HAL_Headers} ${Ancona_HAL_Generic_Code} ${Ancona_HAL_Generic_Headers})

target_link_libraries(Ancona_HAL PUBLIC SDL2)
target_link_libraries(Ancona_HAL PUBLIC SDL2_image)
install(TARGETS Ancona_HAL DESTINATION lib)

