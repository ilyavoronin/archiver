cmake_minimum_required(VERSION 3.12)
project(archiver)

set(CMAKE_CXX_STANDARD 17)

include_directories("C:/Users/voron/Documents/prog/projects/archiver/include/")

add_executable(archiver src/main.cpp src/Archiver.cpp include/Archiver.h)