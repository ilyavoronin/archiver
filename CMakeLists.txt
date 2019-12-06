cmake_minimum_required(VERSION 3.12)
project(archiver)

set(CMAKE_CXX_STANDARD 17)

include_directories("C:/Users/voron/Documents/prog/projects/archiver/include/")

add_executable(archiver src/main.cpp
        src/Archiver.cpp include/Archiver.h
        src/Symbol.cpp include/Symbol.h
        src/Reader.cpp include/Reader.h
        src/Writer.cpp include/Writer.h
        src/HuffmanCoding.cpp include/HuffmanCoding.h
        src/DataInfo.cpp include/DataInfo.h
        src/AString.cpp include/AString.h src/HuffmanTree.cpp include/HuffmanTree.h src/BWT.cpp include/BWT.h src/SuffixSort.cpp include/SuffixSort.h src/MTF.cpp include/MTF.h)

add_subdirectory(tests)