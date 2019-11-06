project(archiver_tests)
add_subdirectory(lib/googletest-release-1.10.0)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


add_executable(archiver_tests_run test.cpp)
target_link_libraries(archiver_tests_run gtest gtest_main)