#include "Writer.h"
#include "AString.h"
#include <iostream>

Writer::Writer(std::string outputFileName, int bufSize_, Mode mode = STD) {
    if (mode == STD) {
        out.open(outputFileName);
    }
    if (mode == BIN) {
        out.open(outputFileName, std::ios::binary);
    }
    if (mode == APP) {
        out.open(outputFileName, std::ios::app);
    }
    if (mode == BINAPP) {
        out.open(outputFileName, std::ios::binary | std::ios::app);
    }
    bufSize = bufSize_;
    buf = new char[bufSize];
}

Writer::~Writer() {
    delete[] buf;
    if (out.is_open()) {
        out.close();
    }
}

void Writer::write(String <Symbol> &output) {
    for (int i = 0; i < (int)output.size(); i++) {
        buf[i] = output[i].get_char();
    }
    out.write(buf, output.size());
}

void Writer::write(int n) {
    for (int i = 0; i < 4; i++) {
        char c = 0;
        for (int j = 0; j < 8; j++) {
            if (((1 << (i * 8 + j)) & n) != 0) {
                c |= (1 << j);
            }
        }
        out << c;
    }
}

void Writer::close() {
    out.close();
}