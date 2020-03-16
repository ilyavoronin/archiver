#include "Reader.h"

Reader::Reader(std::string input_file_name, int buf_size, Mode mode  = STD) {
    if (mode == BIN) {
        in_.open(input_file_name, std::ios::binary);
    }
    else {
        in_.open(input_file_name);
    }
    cnt_read_ = 0;
    buf_size_ = buf_size * 1.1;
    buf_ = new char[buf_size_];
}

Reader::~Reader() {
    delete[] buf_;
    if (in_.is_open()) {
        in_.close();
    }
}

bool Reader::read(String <mchar> &input, int input_size) {
    if (input_size > buf_size_) {
        buf_size_ = input_size;
        delete[] buf_;
        buf_ = new char[buf_size_];
    }
    in_.read(buf_, input_size);
    int sucRead = (int)in_.gcount();
    input.resize(sucRead);
    for (int i = 0; i < sucRead; i++) {
        input[i] = buf_[i];
    }
    cnt_read_ += sucRead;
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
    cnt_read_ += 4;
}

bool Reader::isEOF() {
    in_.peek();
    return in_.eof();
}

 void Reader::close() {
    in_.close();
}