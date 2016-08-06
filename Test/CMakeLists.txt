if(BuildTests AND NOT RAFT_IS_ANDROID)
    add_subdirectory(ExtLibs/gtest-1.7.0)
    add_subdirectory(Unit)
endif(BuildTests AND NOT RAFT_IS_ANDROID)
