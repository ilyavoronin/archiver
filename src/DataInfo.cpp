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
        buf_str += Symbol(c);
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
        buf_str += c;
    }
}

void DataInfo::write(Symbol c) {
    buf_str += c;
}

void DataInfo::write(String <Symbol> &newStr) {
    write((int)newStr.size());
    buf_str += newStr;
}

void DataInfo::write(String <bool> &newStr) {
    auto charStr = newStr.toSymb();
    write((int)charStr.size());
    buf_str += charStr;
}

void DataInfo::writeToFile(Writer &writer) {
    beginNewBlock();
    writer.write((int)str.size());
    writer.write(str);
}

void DataInfo::readFromFile(Reader &reader) {
    int inputSize;
    pos = 0;
    reader.read(inputSize);
    reader.read(str, inputSize);

}

void DataInfo::read(int &n) {
    beginNewBlock();
    n = 0;
    for (int i = 0; i < 4; i++) {
        uint8_t c = str[pos++].get();
        for (int j = 0; j < 8; j++) {
            if (((1 << j) & c) != 0) {
                n |= (1 << (i * 8 + j));
            }
        }
    }
}

void DataInfo::read(short int &n) {
    beginNewBlock();
    n = 0;
    for (int i = 0; i < 2; i++) {
        char c = str[pos++].toChar();
        for (int j = 0; j < 8; j++) {
            if (((1 << j) & c) != 0) {
                n |= (1 << (i * 8 + j));
            }
        }
    }
}

Symbol DataInfo::read() {
    beginNewBlock();
    return str[pos++];
}

void DataInfo::read(String <Symbol> &chars) {
    beginNewBlock();
    int size;
    read(size);
    chars.resize(size);
    for (int i = pos; i < pos + size; i++) {
        chars[i - pos] = str[i];
    }
    pos += size;
}

void DataInfo::read(String <bool> &bin) {
    beginNewBlock();
    int size;
    read(size);
    bin.resize(size * 8);
    for (int i = pos; i < pos + size; i++) {
        char c = str[i].toChar();
        for (int j = 0; j < 8; j++) {
            if (((1 << j) & c) != 0) {
                bin.set((i - pos) * 8 + j, 1);
            }
            else {
                bin.set((i - pos) * 8 + j, 0);
            }
        }
    }
    pos += size;
}

void DataInfo::beginNewBlock() {
    if (buf_str.size() == 0) {
        return;
    }
    str.insertBegin(buf_str);
    buf_str.clear();
}