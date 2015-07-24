file(GLOB_RECURSE TestFiles *.cpp *.hpp)

include_directories(${gtest_SOURCE_DIR}/include)
set(TEST_LIBS ${ANCONA_LIBS} ${ANCONA_EXT_LIBS} gtest_main)

add_executable(project_tests ${TestFiles})
target_link_libraries(project_tests ${TEST_LIBS})
