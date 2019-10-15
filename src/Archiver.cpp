#include "Archiver.h"
#include "Symbol.h"
#include "Reader.h"
#include "Writer.h"
#include <fstream>

void Archiver::zip_block(std::vector <Symbol> &block) {

}

void Archiver::zip(std::string inputFileName, std::string outputFileName) {
    std::vector <Symbol> block(BLOCK_SIZE);
    Reader reader(inputFileName, BLOCK_SIZE, Reader::Mode::BIN);
    Writer writer(outputFileName, BLOCK_SIZE, Writer::Mode::BIN);
    while(!reader.isEOF()) {
        reader.read(block);
        zip_block(block);
        writer.write(block);
    }
}

void Archiver::unzip(std::string inputFileName, std::string outputFileName) {

}