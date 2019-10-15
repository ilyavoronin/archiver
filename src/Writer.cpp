#include "Writer.h"
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
    out.close();
}

void Writer::write(std::vector<Symbol> &output) {
    for (int i = 0; i < (int)output.size(); i++) {
        buf[i] = output[i].toChar();
    }
    out.write(buf, output.size());
}