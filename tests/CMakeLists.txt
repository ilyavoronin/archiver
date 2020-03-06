project(archiver_tests)


add_executable(archiver_tests_run
        ../core/src/Archiver.cpp ../core/include/Archiver.h
        ../core/src/Symbol.cpp ../core/include/Symbol.h
        ../core/src/Reader.cpp ../core/include/Reader.h
        ../core/src/Writer.cpp ../core/include/Writer.h
        ../core/src/HuffmanCoding.cpp ../core/include/HuffmanCoding.h
        ../core/src/DataInfo.cpp ../core/include/DataInfo.h
        ../core/src/AString.cpp ../core/include/AString.h
        test.cpp TestSymbol.cpp TestString.cpp TestDataInfo.cpp
        TestReaderWriter.cpp ../core/src/HuffmanTree.cpp
        ../core/include/HuffmanTree.h TestHuffmanTree.cpp
        TestArchiver.cpp ../core/src/BWT.cpp ../core/include/BWT.h
        ../core/src/SuffixSort.cpp ../core/include/SuffixSort.h TestSuffixSort.cpp
        TestBWT.cpp ../core/src/MTF.cpp ../core/include/MTF.h TestMTF.cpp ../core/src/RLE2.cpp ../core/include/RLE2.h TestRLE2.cpp)
target_link_libraries(archiver_tests_run gtest gtest_main)