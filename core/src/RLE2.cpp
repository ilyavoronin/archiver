#include "RLE2.h"

void RLE2::encode(String <mchar> &data, DataInfo &data_info) {
    int run_length = 1;
    String <mchar> res;
    for (int i = 0; i < data.size(); i++) {
        if (i < data.size() - 1 && data[i] == data[i + 1]) {
            run_length++;
        }
        else {
            int bit_length = 0;
            run_length--;
            while ((1 << bit_length) <= run_length) {
                res.add(0);
                bit_length++;
            }
            for (int j = bit_length - 1; j >= 0; j--) {
                if (((1 << j) & run_length) != 0) {
                    res.add(1);
                }
                else {
                    res.add(0);
                }
            }
            if (run_length == 0) {
                res.add(1);
            }
            run_length = 1;
            res.add(data[i]);
        }
    }
    std::swap(data, res);
}

void RLE2::decode(String <mchar> &data, DataInfo &data_info) {
    String <mchar> res;
    int i = 0;
    while (i < data.size()) {
        int bit_length = 0;
        while (data[i] == 0) {
            bit_length++;
            i++;
        }
        int run_length = 0;
        if (bit_length == 0) {
            i += 1;
        }
        else {
            for (int j = i; j < i + bit_length; j++) {
                run_length = run_length*2 + data[j];
            }
            i += bit_length;
        }
        run_length++;
        for (int j = 0; j < run_length; j++) {
            res.add(data[i]);
        }
        i++;
    }
    std::swap(data, res);
}