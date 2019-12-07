cmake_minimum_required(VERSION 3.12)
project(archiver)

set(CMAKE_CXX_STANDARD 17)

include_directories("C:/Users/voron/Documents/prog/projects/archiver/core/include/")

add_executable(archiver core/src/main.cpp
        core/src/Archiver.cpp core/include/Archiver.h
        core/src/Symbol.cpp core/include/Symbol.h
        core/src/Reader.cpp core/include/Reader.h
        core/src/Writer.cpp core/include/Writer.h
        core/src/HuffmanCoding.cpp core/include/HuffmanCoding.h
        core/src/DataInfo.cpp core/include/DataInfo.h
        core/src/AString.cpp core/include/AString.h
        core/src/HuffmanTree.cpp core/include/HuffmanTree.h
        core/src/BWT.cpp core/include/BWT.h
        core/src/SuffixSort.cpp core/include/SuffixSort.h
        core/src/MTF.cpp core/include/MTF.h)

add_subdirectory(tests)