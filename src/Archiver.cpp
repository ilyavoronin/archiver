#include "Archiver.h"
#include "Symbol.h"
#include "Reader.h"
#include "Writer.h"
#include "HuffmanCoding.h"
#include "BWT.h"
#include "MTF.h"


void Archiver::zip_block(String <Symbol> &block, DataInfo &dataInfo) {
    dataInfo.beginNewBlock();
    BWT().encode(block, dataInfo);

    dataInfo.beginNewBlock();
    MTF().encode(block);

    dataInfo.beginNewBlock();
    HuffmanCoding().encode(block, dataInfo);
}

void Archiver::unzip_block(String <Symbol> &block, DataInfo &dataInfo) {
    HuffmanCoding().decode(block, dataInfo);

    MTF().decode(block);

    BWT().decode(block, dataInfo);
}

void Archiver::zip(std::string inputFileName, std::string outputFileName) {
    String <Symbol> block(BLOCK_SIZE);
    Reader reader(inputFileName, BLOCK_SIZE, Reader::Mode::BIN);
    Writer writer(outputFileName, BLOCK_SIZE, Writer::Mode::BIN);
    while(!reader.isEOF()) {
        DataInfo dataInfo;
        reader.read(block, BLOCK_SIZE);
        zip_block(block, dataInfo);
        writer.write((int)block.size());
        writer.write(block);
        dataInfo.writeToFile(writer);
    }
}

void Archiver::unzip(std::string inputFileName, std::string outputFileName) {
    String <Symbol> block;
    Reader reader(inputFileName, BLOCK_SIZE, Reader::Mode::BIN);
    Writer writer(outputFileName, BLOCK_SIZE, Writer::Mode::BIN);
    while(!reader.isEOF()) {
        DataInfo dataInfo;
        int inputSize;
        reader.read(inputSize);
        reader.read(block, inputSize);
        dataInfo.readFromFile(reader);
        unzip_block(block, dataInfo);
        writer.write(block);
    }
}