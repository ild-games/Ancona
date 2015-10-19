set(PrototypeGameLib EditorMap_Lib)
set(PrototypeName EditorMap)

add_subdirectory(Src/EditorMap/EditorMapLib)

if(ANDROID)
    set(EditorMapSrc Src/EditorMap/Platforms/Android/main.cpp)
endif(ANDROID)

if(DESKTOP)
    set(EditorMapSrc Src/EditorMap/Platforms/Desktop/main.cpp)
endif(DESKTOP)

ancona_add_target(EditorMap LINK_SFML
    SRC ${EditorMapSrc}
    LIBS EditorMap_Lib ${ANCONA_LIBS} ${ANCONA_EXT_LIBS}
    WHOLE_STATIC_LIBS ${ANCONA_WHOLE_EXT_LIBS}
    PLATFORMS ANDROID DESKTOP
    INCLUDES ${CMAKE_CURRENT_LIST_DIR}/Src)

if(ANDROID)
    set(AssetOutputDir ${CMAKE_BINARY_DIR}/Android/EditorMap/assets)
    set(COMPILED_PRJ_SRC_DIR)
elseif(DESKTOP)
    set(AssetOutputDir ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/EditorMap)
    set(COMPILED_PRJ_SRC_DIR ${CMAKE_SOURCE_DIR}/)
endif()

configure_file(Config.txt ${AssetOutputDir}/Config.txt @ONLY)
configure_file(save.dat ${AssetOutputDir}/save.dat COPYONLY)
file(COPY Maps DESTINATION ${AssetOutputDir})
