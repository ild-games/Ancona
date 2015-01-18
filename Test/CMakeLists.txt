if(BuildPrototypes)
    add_subdirectory(Prototype)
endif(BuildPrototypes)

if(BuildTests)
    add_subdirectory(ExtLibs/gtest-1.7.0)
    add_subdirectory(Unit)
endif(BuildTests)
