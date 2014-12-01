file(GLOB_RECURSE SOURCE *.cpp)
file(GLOB_RECURSE HEADERS *.hpp)

#ConfigTest should be changed to prototype name
set(PrototypeName FlappyBirdTest)

add_executable(${PrototypeName} ${SOURCE} ${HEADERS})

target_link_libraries (${PrototypeName} ${Libs})
