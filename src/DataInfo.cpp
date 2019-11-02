#include "DataInfo.h"

DataInfo::DataInfo() {
    pos = 0;
}

void DataInfo::write(short int n) {
    for (int i = 0; i < 2; i++) {
        uint8_t c = 0;
        for (int j = 0; j < 8; j++) {
            if (((1 << (i * 8 + j)) & n) != 0) {
                c |= (1 << j);
            }
        }
        str += Symbol(c);
    }
}

void DataInfo::write(int n) {
    for (int i = 0; i < 4; i++) {
        uint8_t c = 0;
        for (int j = 0; j < 8; j++) {
            if (((1 << (i * 8 + j)) & n) != 0) {
                c |= (1 << j);
            }
        }
        str += c;
    }
}

void DataInfo::write(Symbol c) {
    str += c;
}

void DataInfo::writeToFile(Writer &writer) {
    writer.write(str.size());
    writer.write(str);
}