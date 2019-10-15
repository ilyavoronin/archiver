#include "Archiver.h"
#include "Symbol.h"
#include "Reader.h"
#include <fstream>
#include <vector>

void Archiver::zip(std::string inputFileName, std::string outputFileName) {
    std::vector <Symbol> block(BLOCK_SIZE);
    Reader reader(inputFileName, BLOCK_SIZE, Reader::Mode::BIN);
    while(!reader.isEOF()) {
        reader.read(block);

    }
}

void Archiver::unzip(std::string inputFileName, std::string outputFileName) {

}