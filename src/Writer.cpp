#include "Writer.h"

Writer::Writer(std::string outputFileName, int bufSize_, Mode mode = STD) {
    switch (mode) {
        case 0 : out.open(outputFileName);
        case 1 : out.open(outputFileName, std::ios::binary);
        case 2 : out.open(outputFileName, std::ios::app);
        case 3 : out.open(outputFileName, std::ios::binary | std::ios::app);
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