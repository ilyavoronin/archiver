cmake_minimum_required(VERSION 3.12)
project(archiver)

set(CMAKE_CXX_STANDARD 17)

include_directories(core/include/)
include_directories(ui/include/)

# Download and unpack googletest at configure time
configure_file(tests/CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include")
endif()

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
        core/src/MTF.cpp core/include/MTF.h
        core/include/IDataEncoder.h
        ui/src/ConsoleUI.cpp ui/include/ConsoleUI.h core/include/ECoders.h core/src/RLE2.cpp core/include/RLE2.h core/src/RLE.cpp core/include/RLE.h)

add_subdirectory(tests)