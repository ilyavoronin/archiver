#include "Writer.h"
#include "AString.h"
#include <iostream>

Writer::Writer(std::string outputFileName, int bufSize_, Mode mode = STD) {
    if (mode == STD) {
        out_.open(outputFileName);
    }
    if (mode == BIN) {
        out_.open(outputFileName, std::ios::binary);
    }
    if (mode == APP) {
        out_.open(outputFileName, std::ios::app);
    }
    if (mode == BINAPP) {
        out_.open(outputFileName, std::ios::binary | std::ios::app);
    }
    buf_size_ = bufSize_ * 1.1;
    buf_ = new char[buf_size_];
}

Writer::~Writer() {
    delete[] buf_;
    if (out_.is_open()) {
        out_.close();
    }
}

void Writer::write(String <Symbol> &output) {
    if (buf_size_ < output.size()) {
        delete [] buf_;
        buf_size_ = output.size();
        buf_ = new char[buf_size_];
    }
    for (int i = 0; i < (int)output.size(); i++) {
        buf_[i] = output[i].get_char();
    }
    out_.write(buf_, output.size());
}

void Writer::write(int n) {
    for (int i = 0; i < 4; i++) {
        char c = 0;
        for (int j = 0; j < 8; j++) {
            if (((1 << (i * 8 + j)) & n) != 0) {
                c |= (1 << j);
            }
        }
        out_ << c;
    }
}

void Writer::close() {
    out_.close();
}