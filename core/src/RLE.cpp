#include "RLE.h"
#include "HuffmanCoding.h"
#include "ArithmeticCoding.h"
#include <iostream>

void RLE::encode(String <mchar> &data, DataInfo &data_info) {
    int run_length = 1;
    String <mchar> res;
    String <mchar> runs;
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
                write_int(run_length - 2, runs);
            }
            run_length = 1;
        }
    }
    ArithmeticCoding().encode(runs, data_info);
    data_info.beginNewBlock();
    data_info.write(runs);
    std::swap(data, res);
}

void RLE::decode(String <mchar> &data, DataInfo &data_info) {
    String <mchar> res;
    String <mchar> runs;
    data_info.read(runs);
    ArithmeticCoding().decode(runs, data_info);
    int i = 0;
    if (runs.size() == 0) {
        i = 0;
    }
    int runs_i = 0;
    while (i < data.size()) {
        if (i == data.size() - 1 || data[i] != data[i + 1]) {
            res.add(data[i]);
        }
        else {
            mchar symb = data[i];
            i++;
            int run_length = read_int(runs_i, runs) + 2;
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
void RLE::write_int(int n, String <mchar> &runs) {
    int bit_length = 1;
    while ((1 << bit_length) <= n) {
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
        runs.add(byte);
    }
}

int RLE::read_int(int &i, String <mchar> &runs) {
    int k = 0;
    int res = 0;
    while (true) {
        for (int j = 0; j < 7; j++) {
            if ((runs[i] & (1 << j)) != 0) {
                res |= (1 << (k * 7 + j));
            }
        }
        if ((runs[i] & (1 << 7)) != 0) {
            break;
        }
        k++;
        i++;
    }
    i++;
    return res;
}