#include "DataInfo.h"

DataInfo::DataInfo() {
    pos_ = 0;
}

void DataInfo::write(short int n) {
    for (int i = 0; i < 2; i++) {
        uint8_t c = 0;
        for (int j = 0; j < 8; j++) {
            if (((1 << (i * 8 + j)) & n) != 0) {
                c |= (1 << j);
            }
        }
        buf_str_ += Symbol(c);
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
        buf_str_ += c;
    }
}

void DataInfo::write(Symbol c) {
    buf_str_ += c;
}

void DataInfo::write(String <Symbol> &new_str) {
    write((int)new_str.size());
    buf_str_ += new_str;
}

void DataInfo::write(String <bool> &new_str) {
    auto charStr = new_str.toSymb();
    write(int{charStr.size()});
    buf_str_ += charStr;
}

void DataInfo::writeToFile(Writer &writer) {
    beginNewBlock();
    writer.write(int{str_.size()});
    writer.write(str_);
}

void DataInfo::read(int &n) {
    beginNewBlock();
    n = 0;
    for (int i = 0; i < 4; i++) {
        uint8_t c = str_[pos_++].get();
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
        char c = str_[pos_++].toChar();
        for (int j = 0; j < 8; j++) {
            if (((1 << j) & c) != 0) {
                n |= (1 << (i * 8 + j));
            }
        }
    }
}

Symbol DataInfo::read() {
    beginNewBlock();
    return str_[pos_++];
}

void DataInfo::read(String <Symbol> &chars) {
    beginNewBlock();
    int size;
    read(size);
    chars.resize(size);
    for (int i = pos_; i < pos_ + size; i++) {
        chars[i - pos_] = str_[i];
    }
    pos_ += size;
}

void DataInfo::read(String <bool> &bin) {
    beginNewBlock();
    int size;
    read(size);
    bin.resize(size * 8);
    for (int i = pos_; i < pos_ + size; i++) {
        char c = str_[i].toChar();
        for (int j = 0; j < 8; j++) {
            if (((1 << j) & c) != 0) {
                bin.set((i - pos_) * 8 + j, 1);
            }
            else {
                bin.set((i - pos_) * 8 + j, 0);
            }
        }
    }
    pos_ += size;
}

void DataInfo::readFromFile(Reader &reader) {
    int inputSize;
    pos_ = 0;
    reader.read(inputSize);
    reader.read(str_, inputSize);

}

void DataInfo::beginNewBlock() {
    if (buf_str_.size() == 0) {
        return;
    }
    str_.insertBegin(buf_str_);
    buf_str_.clear();
}