#include "Archiver.h"
#include "Symbol.h"
#include "Reader.h"
#include "Writer.h"
#include "HuffmanCoding.h"


void Archiver::zip_block(String <Symbol> &block, DataInfo &dataInfo) {
    HuffmanCoding().encode(block, dataInfo);
}

void Archiver::zip(std::string inputFileName, std::string outputFileName) {
    String <Symbol> block(BLOCK_SIZE);
    Reader reader(inputFileName, BLOCK_SIZE, Reader::Mode::BIN);
    Writer writer(outputFileName, BLOCK_SIZE, Writer::Mode::BIN);
    DataInfo dataInfo;
    while(!reader.isEOF()) {
        reader.read(block);
        zip_block(block, dataInfo);
        writer.write(block);
    }
}

void Archiver::unzip(std::string inputFileName, std::string outputFileName) {

}