file(GLOB_RECURSE SOURCE *.cpp)
file(GLOB_RECURSE HEADERS *.hpp)

#ConfigTest should be changed to prototype name
set(PrototypeName ConfigTest)

add_executable(${PrototypeName} ${SOURCE} ${HEADERS})

target_link_libraries (${PrototypeName} ${Ancona_Libs} ${SFML_LIBS})

#This line was added to copy the config file to the build directory
configure_file(ConfigTest.txt ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ConfigTest.txt COPYONLY)
