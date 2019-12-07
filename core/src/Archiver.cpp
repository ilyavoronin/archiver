#include "Archiver.h"

#include "Symbol.h"
#include "Reader.h"
#include "Writer.h"
#include "HuffmanCoding.h"
#include "BWT.h"
#include "MTF.h"

void Archiver::zip(std::string input_file_name, std::string output_file_name) {
    String <Symbol> block(kBlockSize);
    Reader reader(input_file_name, kBlockSize, Reader::Mode::BIN);
    Writer writer(output_file_name, kBlockSize, Writer::Mode::BIN);
    while(!reader.isEOF()) {
        DataInfo data_info;
        reader.read(block, kBlockSize);
        zipBlock(block, data_info);
        writer.write(int{block.size()});
        writer.write(block);
        data_info.writeToFile(writer);
    }
}

void Archiver::unzip(std::string input_file_name, std::string output_file_name) {
    String <Symbol> block;
    Reader reader(input_file_name, kBlockSize, Reader::Mode::BIN);
    Writer writer(output_file_name, kBlockSize, Writer::Mode::BIN);
    while(!reader.isEOF()) {
        DataInfo data_info;
        int input_size;
        reader.read(input_size);
        reader.read(block, input_size);
        data_info.readFromFile(reader);
        unzipBlock(block, data_info);
        writer.write(block);
    }
}

void Archiver::zipBlock(String <Symbol> &block, DataInfo &data_info) {
    data_info.beginNewBlock();
    BWT().encode(block, data_info);

    data_info.beginNewBlock();
    MTF().encode(block);

    data_info.beginNewBlock();
    HuffmanCoding().encode(block, data_info);
}

void Archiver::unzipBlock(String <Symbol> &block, DataInfo &data_info) {
    HuffmanCoding().decode(block, data_info);

    MTF().decode(block);

    BWT().decode(block, data_info);
}