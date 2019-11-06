#include "Reader.h"

Reader::Reader(std::string inputFileName, int bufSize_, Mode mode  = STD) {
    if (mode == BIN) {
        in.open(inputFileName, std::ios::binary);
    }
    else {
        in.open(inputFileName);
    }
    cntRead = 0;
    bufSize = bufSize_;
    buf = new char[bufSize];
}

Reader::~Reader() {
    delete[] buf;
    in.close();
}

bool Reader::read(String <Symbol> &input, int inputSize) {
    in.read(buf, inputSize);
    int sucRead = (int)in.gcount();
    input.resize(sucRead);
    for (int i = 0; i < sucRead; i++) {
        input[i] = buf[i];
    }
    cntRead += sucRead;
    return sucRead == inputSize;
}

bool Reader::isEOF() {
    in.peek();
    return in.eof();
}

void Reader::read(int &n) {
    n = 0;
    for (int i = 0; i < 4; i++) {
        char c = in.get();
        for (int j = 0; j < 8; j++) {
            if (((1 << j) & c) != 0) {
                n |= (1 << (8 * i + j));
            }
        }
    }
    cntRead += 4;
 }