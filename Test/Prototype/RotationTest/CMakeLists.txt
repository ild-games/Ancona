set(PrototypeGameLib Rotation_Lib)
set(PrototypeName RotationTest)

add_subdirectory(Src/RotationTest/RotationLib)

if(ANDROID)
    set(RotationSrc Src/RotationTest/Platforms/Android/main.cpp)
endif(ANDROID)

if(DESKTOP)
    set(RotationSrc Src/RotationTest/Platforms/Desktop/main.cpp)
endif(DESKTOP)

ancona_add_target(RotationTest LINK_SFML
    SRC ${RotationSrc}
    LIBS Rotation_Lib ${ANCONA_LIBS} ${ANCONA_EXT_LIBS}
    WHOLE_STATIC_LIBS ${ANCONA_WHOLE_EXT_LIBS}
    PLATFORMS ANDROID DESKTOP
    INCLUDES ${CMAKE_CURRENT_LIST_DIR}/Src)

if(ANDROID)
    set(AssetOutputDir ${CMAKE_BINARY_DIR}/Android/RotationTest/assets)
    set(COMPILED_PRJ_SRC_DIR)
elseif(DESKTOP)
    set(AssetOutputDir ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/RotationTest)
    set(COMPILED_PRJ_SRC_DIR ${CMAKE_SOURCE_DIR}/)
endif()

configure_file(Config.txt ${AssetOutputDir}/Config.txt @ONLY)
configure_file(save.dat ${AssetOutputDir}/save.dat COPYONLY)
file(COPY Maps DESTINATION ${AssetOutputDir})
