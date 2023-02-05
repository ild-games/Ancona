IF(RAFT_IS_ANDROID)
    file(GLOB_RECURSE Ancona_HAL_Code ${ANCONA_HAL_ID}/*Impl.cpp ${ANCONA_HAL_ID}/*Impl.Android.cpp)
    file(GLOB_RECURSE Ancona_HAL_Headers ${ANCONA_HAL_ID}/*Impl.hpp ${ANCONA_HAL_ID}/*Impl.Desktop.cpp)
ELSEIF(RAFT_IS_IOS)
    file(GLOB_RECURSE Ancona_HAL_Code ${ANCONA_HAL_ID}/*Impl.cpp ${ANCONA_HAL_ID}/*Impl.iOS.mm)
    file(GLOB_RECURSE Ancona_HAL_Headers ${ANCONA_HAL_ID}/*Impl.hpp ${ANCONA_HAL_ID}/*Impl.iOS.hpp)
ELSEIF(RAFT_IS_MACOS)
    file(GLOB_RECURSE Ancona_HAL_Code ${ANCONA_HAL_ID}/*Impl.cpp ${ANCONA_HAL_ID}/*Impl.macOS.mm)
    file(GLOB_RECURSE Ancona_HAL_Headers ${ANCONA_HAL_ID}/*Impl.hpp ${ANCONA_HAL_ID}/*Impl.macOS.hpp)
ELSEIF(RAFT_IS_DESKTOP)
    file(GLOB_RECURSE Ancona_HAL_Code ${ANCONA_HAL_ID}/*Impl.cpp ${ANCONA_HAL_ID}/*Impl.Desktop.cpp)
    file(GLOB_RECURSE Ancona_HAL_Headers ${ANCONA_HAL_ID}/*Impl.hpp ${ANCONA_HAL_ID}/*Impl.Desktop.hpp)
ENDIF()

file(GLOB Ancona_HAL_Generic_Code *.cpp)
file(GLOB Ancona_HAL_Generic_Headers *.hpp *.inl)

add_library(Ancona_HAL ${Ancona_HAL_Code} ${Ancona_HAL_Headers} ${Ancona_HAL_Generic_Code} ${Ancona_HAL_Generic_Headers})

target_link_libraries(Ancona_HAL PUBLIC SDL2)
target_link_libraries(Ancona_HAL PUBLIC SDL2_image)
install(TARGETS Ancona_HAL DESTINATION lib)

