#include "Reader.h"

Reader::Reader(std::string inputFileName, bool isBinary, int bufSize_) {
    if (isBinary) {
        in.open(inputFileName, std::ios::binary);
    }
    else {
        in.open(inputFileName);
    }
    sucRead = 0;
    isEOF = false;
    bufSize = bufSize_;
    buf = new char[bufSize];
}

bool Reader::read(std::vector <Symbol> &input) {
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