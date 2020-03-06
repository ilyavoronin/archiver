#include "Archiver.h"

#include <algorithm>

#include "Symbol.h"
#include "Reader.h"
#include "Writer.h"
#include "HuffmanCoding.h"
#include "BWT.h"
#include "MTF.h"
#include "RLE2.h"

Archiver::Archiver() {
    coders = {
        {C_BWT, new BWT},
        {C_MTF, new MTF},
        {C_HUFFMAN, new HuffmanCoding},
        {C_RLE2, new RLE2}
    };
}

Archiver::~Archiver() {
    for (auto elem : coders) {
        delete elem.second;
    }
}

void Archiver::zip(std::vector <Coders> algorithm, std::string input_file_name, std::string output_file_name) {
    auto coding_sequence = toCoderSequence(algorithm);
    String <Symbol> block(kBlockSize);
    Reader reader(input_file_name, kBlockSize, Reader::Mode::BIN);
    Writer writer(output_file_name, kBlockSize, Writer::Mode::BIN);
    writer.write(int(algorithm.size()));
    for (auto encoder : algorithm) {
        writer.write(int(encoder));
    }
    while(!reader.isEOF()) {
        DataInfo data_info;
        reader.read(block, kBlockSize);
        zipBlock(block, data_info, coding_sequence);
        writer.write(int{block.size()});
        writer.write(block);
        data_info.writeToFile(writer);
    }
}

void Archiver::unzip(std::string input_file_name, std::string output_file_name) {
    String <Symbol> block;
    Reader reader(input_file_name, kBlockSize, Reader::Mode::BIN);
    Writer writer(output_file_name, kBlockSize, Writer::Mode::BIN);
    std::vector <Coders> algorithm;
    int cnt_coders;
    reader.read(cnt_coders);
    for (int i = 0; i < cnt_coders; i++) {
        int coder;
        reader.read(coder);
        algorithm.push_back(Coders(coder));
    }
    auto decoding_sequence = toCoderSequence(algorithm);
    std::reverse(decoding_sequence.begin(), decoding_sequence.end());
    while(!reader.isEOF()) {
        DataInfo data_info;
        int input_size;
        reader.read(input_size);
        reader.read(block, input_size);
        data_info.readFromFile(reader);
        unzipBlock(block, data_info, decoding_sequence);
        writer.write(block);
    }
}

void Archiver::zipBlock(String <Symbol> &block, DataInfo &data_info, std::vector <IDataEncoder *> coding_sequence) {
    for (auto encoder : coding_sequence) {
        data_info.beginNewBlock();
        encoder->encode(block, data_info);
    }
}

void Archiver::unzipBlock(String <Symbol> &block, DataInfo &data_info, std::vector <IDataEncoder *> decoding_sequence) {
    for (auto decoder : decoding_sequence) {
        decoder->decode(block, data_info);
    }
}

std::vector <IDataEncoder *> Archiver::toCoderSequence(std::vector<Coders> algorithm) {
    std::vector <IDataEncoder *> res;
    for (auto algo : algorithm) {
        res.push_back(coders[algo]);
    }
    return res;
}