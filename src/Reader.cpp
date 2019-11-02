#include "Reader.h"

Reader::Reader(std::string inputFileName, int bufSize_, Mode mode  = STD) {
    if (mode == BIN) {
        in.open(inputFileName, std::ios::binary);
    }
    else {
        in.open(inputFileName);
    }
    sucRead = 0;
    eof = false;
    bufSize = bufSize_;
    buf = new char[bufSize];
}

Reader::~Reader() {
    delete[] buf;
    in.close();
}

bool Reader::read(String <Symbol> &input) {
    in.read(buf, bufSize);
    sucRead = (int)in.gcount();
    if (sucRead < bufSize) {
        eof = true;
    }
    input.resize(sucRead);
    for (int i = 0; i < sucRead; i++) {
        input[i] = buf[i];
    }
    return sucRead == bufSize;
}

bool Reader::isEOF() {
    return eof;
}