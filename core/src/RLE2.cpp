#include "RLE2.h"

#include "ArithmeticCoding.h"

void RLE2::encode(String <mchar> &data, DataInfo &data_info) {
    int run_length = 1;
    String <mchar> res;
    String <bool> runs;
    for (int i = 0; i < data.size(); i++) {
        if (i < data.size() - 1 && data[i] == data[i + 1]) {
            run_length++;
        }
        else {
            int bit_length = 0;
            run_length--;
            while ((1 << bit_length) <= run_length) {
                runs.add(0);
                bit_length++;
            }
            for (int j = bit_length - 1; j >= 0; j--) {
                if (((1 << j) & run_length) != 0) {
                    runs.add(1);
                }
                else {
                    runs.add(0);
                }
            }
            if (run_length == 0) {
                runs.add(1);
            }
            run_length = 1;
            res.add(data[i]);
        }
    }
    ArithmeticCoding().encodeBinary(runs, data_info);
    data_info.beginNewBlock();
    data_info.write(runs);
    std::swap(data, res);
}

void RLE2::decode(String <mchar> &data, DataInfo &data_info) {
    String <mchar> res;
    String <bool> runs;
    data_info.read(runs);
    ArithmeticCoding().decodeBinary(runs, data_info);
    int i = 0;
    int runs_i = 0;
    while (i < data.size()) {
        int bit_length = 0;
        while (runs[runs_i] == 0) {
            bit_length++;
            runs_i++;
        }
        int run_length = 0;
        if (bit_length == 0) {
            runs_i += 1;
        }
        else {
            for (int j = runs_i; j < runs_i + bit_length; j++) {
                run_length = run_length * 2 + runs[j];
            }
            runs_i += bit_length;
        }
        run_length++;
        for (int j = 0; j < run_length; j++) {
            res.add(data[i]);
        }
        i++;
    }
    std::swap(data, res);
}