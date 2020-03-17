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
        buf_str_ += mchar(c);
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

void DataInfo::write(mchar c) {
    buf_str_ += c;
}

void DataInfo::write(String <mchar> &new_str) {
    write((int)new_str.size());
    buf_str_ += new_str;
}

void DataInfo::write(String <bool> &new_str) {
    auto charStr = new_str.toSymb();
    write(new_str.size());
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
        uint8_t c = str_[pos_++];
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
        char c = str_[pos_++];
        for (int j = 0; j < 8; j++) {
            if (((1 << j) & c) != 0) {
                n |= (1 << (i * 8 + j));
            }
        }
    }
}

mchar DataInfo::read() {
    beginNewBlock();
    return str_[pos_++];
}

void DataInfo::read(String <mchar> &chars) {
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
    int size, bin_size;
    read(bin_size);
    read(size);
    bin.resize(bin_size);
    for (int i = pos_; i < pos_ + size; i++) {
        char c = str_[i];
        for (int j = 0; j < 8; j++) {
            if ((i - pos_) * 8 + j >= bin_size) {
                break;
            }
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