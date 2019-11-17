project(archiver_tests)
add_subdirectory(lib/googletest-release-1.10.0)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


add_executable(archiver_tests_run
        ../src/Archiver.cpp ../include/Archiver.h
        ../src/Symbol.cpp ../include/Symbol.h
        ../src/Reader.cpp ../include/Reader.h
        ../src/Writer.cpp ../include/Writer.h
        ../src/HuffmanCoding.cpp ../include/HuffmanCoding.h
        ../src/DataInfo.cpp ../include/DataInfo.h
        ../src/AString.cpp ../include/AString.h
        test.cpp TestSymbol.cpp TestString.cpp TestDataInfo.cpp TestReaderWriter.cpp ../src/HuffmanTree.cpp ../include/HuffmanTree.h TestHuffmanTree.cpp TestArchiver.cpp ../src/BWT.cpp ../include/BWT.h ../src/SuffixSort.cpp ../include/SuffixSort.h)
target_link_libraries(archiver_tests_run gtest gtest_main)