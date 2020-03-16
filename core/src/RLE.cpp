#include "RLE.h"

void RLE::encode(String <Symbol> &data, DataInfo &data_info) {
    int run_length = 1;
    String <Symbol> res;
    for (int i = 0; i < data.size(); i++) {
        if (i < data.size() - 1 && data[i] == data[i + 1]) {
            run_length++;
        }
        else {
            if (run_length == 1) {
                res.add(data[i]);
            }
            else {
                res.add(data[i]);
                res.add(data[i]);
                write_int(run_length - 2, res);
            }
            run_length = 1;
        }
    }
    std::swap(data, res);
}

void RLE::decode(String <Symbol> &data, DataInfo &data_info) {
    String <Symbol> res;
    int i = 0;
    while (i < data.size()) {
        if (i == data.size() - 1 || data[i] != data[i + 1]) {
            res.add(data[i]);
        }
        else {
            Symbol symb = data[i];
            i += 2;
            int run_length = read_int(i, data) + 2;
            for (int j = 0; j < run_length; j++) {
                res.add(symb);
            }
        }
        i++;
    }
    std::swap(data, res);
}

//we will use only 7 bits of each byte for store integer
//the last bit indicates if it is a last byte in this integer representation
void RLE::write_int(int n, String <Symbol> &res) {
    int bit_length = 1;
    while ((1 << bit_length) < n) {
        bit_length++;
    }
    int kbytes = (bit_length - 1) / 7 + 1;
    for (int i = 0; i < kbytes; i++) {
        char byte = 0;
        for (int j = 0; j < 7; j++) {
            if (((1 << (i * 7 + j)) & n) != 0) {
                byte |= (1 << j);
            }
        }
        if (i == kbytes - 1) {
            byte |= (1 << 7);
        }
        res.add(byte);
    }
}

int RLE::read_int(int &i, String <Symbol> &data) {
    int k = 0;
    int res = 0;
    while (true) {
        for (int j = 0; j < 7; j++) {
            if ((data[i].get() & (1 << j)) != 0) {
                res |= (1 << (k * 7 + j));
            }
        }
        if ((data[i].get() & (1 << 7)) != 0) {
            break;
        }
        k++;
        i++;
    }
    return res;
}