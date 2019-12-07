#include "Reader.h"

Reader::Reader(std::string input_file_name, int buf_size, Mode mode  = STD) {
    if (mode == BIN) {
        in_.open(input_file_name, std::ios::binary);
    }
    else {
        in_.open(input_file_name);
    }
    cntRead_ = 0;
    bufSize_ = buf_size;
    buf_ = new char[bufSize_];
}

Reader::~Reader() {
    delete[] buf_;
    if (in_.is_open()) {
        in_.close();
    }
}

bool Reader::read(String <Symbol> &input, int input_size) {
    in_.read(buf_, input_size);
    int sucRead = (int)in_.gcount();
    input.resize(sucRead);
    for (int i = 0; i < sucRead; i++) {
        input[i] = buf_[i];
    }
    cntRead_ += sucRead;
    return sucRead == input_size;
}

void Reader::read(int &n) {
    n = 0;
    for (int i = 0; i < 4; i++) {
        char c = in_.get();
        for (int j = 0; j < 8; j++) {
            if (((1 << j) & c) != 0) {
                n |= (1 << (8 * i + j));
            }
        }
    }
    cntRead_ += 4;
}

bool Reader::isEOF() {
    in_.peek();
    return in_.eof();
}

 void Reader::close() {
    in_.close();
}