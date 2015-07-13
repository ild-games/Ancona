#ConfigTest should be changed to prototype name
set(PrototypeGameLib Impossible_Lib)
set(PrototypeName ImpossibleDuckTest)

add_subdirectory(Src/ImpossibleDuck/ImpossibleLib)

if(ANDROID)
    set(ImpossibleSrc Src/ImpossibleDuck/Platforms/Android/main.cpp)
endif(ANDROID)

if(DESKTOP)
    set(ImpossibleSrc Src/ImpossibleDuck/Platforms/Desktop/main.cpp)
endif(DESKTOP)

ancona_add_target(ImpossibleDuckProto
    SRC ${ImpossibleSrc}
    LIBS Impossible_Lib ${ANCONA_LIBS} ${ANCONA_EXT_LIBS}
    WHOLE_STATIC_LIBS ${ANCONA_WHOLE_EXT_LIBS}
    PLATFORMS ANDROID DESKTOP
    INCLUDES ${CMAKE_CURRENT_LIST_DIR}/Src)

if(ANDROID)
    set(AssetOutputDir ${CMAKE_BINARY_DIR}/Android/ImpossibleDuckProto/assets)
    set(COMPILED_PRJ_SRC_DIR)
elseif(DESKTOP)
    set(AssetOutputDir ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ImpossibleDuckProto)
    set(COMPILED_PRJ_SRC_DIR ${CMAKE_SRC_DIR}/)
endif()

configure_file(Config.txt ${AssetOutputDir}/Config.txt @ONLY)
configure_file(save.dat ${AssetOutputDir}/save.dat COPYONLY)
file(COPY Maps DESTINATION ${AssetOutputDir})
