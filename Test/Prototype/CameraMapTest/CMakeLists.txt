file(GLOB_RECURSE SOURCE */*.cpp)
file(GLOB_RECURSE HEADERS */*.hpp)

#ConfigTest should be changed to prototype name
set(PrototypeGameLib CameraMapLib)
set(PrototypeName CameraMapTest)

add_library(${PrototypeGameLib} ${SOURCE} ${HEADERS})
add_executable(${PrototypeName} main.cpp)

target_link_libraries(${PrototypeName} ${PrototypeGameLib} ${Libs})
