#include "ArithmeticCoding.h"

void ArithmeticCoding::encode(String <mchar> &data, DataInfo &data_info) {
    if (data.size() == 0) {
        data_info.write(0);
        return;
    }
    unsigned long long left = 0, right = (1ll << kBinaryBlockSize) - 1;
    std::vector <long long> probability;
    std::vector <long long> freq(256, 0);

    int alph_size = 0;
    for (int i = 0; i < data.size(); i++) {
        freq[data[i]]++;
        alph_size = std::max(alph_size, (int)data[i]);
    }
    alph_size++;

    int input_size = (int)data.size();
    data_info.write(alph_size);
    for (int i = 0; i < alph_size; i++) {
        data_info.write((int)freq[i]);
    }
    data_info.write(input_size);

    //initialize probabilities
    probability.push_back(0);
    for (int j = 0; j < alph_size; j++) {
        probability.push_back(probability[j] + ((N - 2) * (freq[j] + 1) / data.size()));
    }
    for (int j = 0; j < alph_size + 1; j++) {
        probability[j] = probability[j] * (N - 2) / probability[alph_size];
    }

    std::vector <bool> result;
    for (int i = 0; i < input_size; i++) {
        unsigned long long prev_left = left;
        left = prev_left + (((right - prev_left + 1) * probability[data[i]]) >> kBinaryBlockSize);
        right = prev_left + (((right - prev_left + 1) * probability[data[i] + 1]) >> kBinaryBlockSize);
        while ((right >> (kBinaryBlockSize - 1)) == (left >> (kBinaryBlockSize - 1))) {
            result.push_back((short)(left >> (kBinaryBlockSize - 1)));
            left = (left % MOD) * 2;
            right = (right % MOD - 1) * 2;
        }
        if (right - left < EPS) {
            for (int j = 0; j < kBinaryBlockSize - kEpsSize; j++) {
                result.push_back((left >> (kBinaryBlockSize - 1)));
                left = (left % MOD) * 2;
            }
            while (left / MOD == 1) {
                result.push_back((left >> (kBinaryBlockSize - 1)));
                left = (left % MOD) * 2;
            }
            right = N - 1;
        }
    }
    unsigned long long middle = (left + right) / 2;
    std::vector <short int> bin_middle;
    while (middle > 0) {
        bin_middle.push_back(middle % 2);
        middle = middle / 2;
    }
    for (int i = 0; i < kBinaryBlockSize - (int)bin_middle.size(); i++) {
        result.push_back(0);
    }
    for (int i = (int)bin_middle.size() - 1; i >= 0; i--) {
        result.push_back(bin_middle[i]);
    }
    data.clear();
    //write final size
    data_info.write(((int)result.size() + 7) / 8);
    for (int i = 0; i < result.size(); i += 8) {
        int byte = 0;
        for (int j = i; j < std::min((int)result.size(), i + 8); j++) {
            if (result[j] == 1) {
                byte = byte | (1 << (j - i));
            }
        }
        data.add(byte);
    }
}

void ArithmeticCoding::decode(String <mchar> &data, DataInfo &data_info) {
    int string_size, decoded_string_size, alph_size;
    data_info.read(alph_size);
    unsigned long long left = 0, right = (1ll << kBinaryBlockSize) - 1;
    std::vector <long long> probability;
    std::vector <bool> bit_data;
    String <mchar> decoded_string;
    std::vector <int> freq;

    if (alph_size == 0) {
        data.clear();
        return;
    }

    freq.resize(alph_size);
    for (int i = 0; i < alph_size; i++) {
        data_info.read(freq[i]);
    }
    data_info.read(decoded_string_size);
    data_info.read(string_size);
    for (int i = 0; i < string_size; i++) {
        uint8_t symbol = data[i];
        for (int j = 0; j < 8; j++) {
            bit_data.push_back((((1 << j) & symbol) != 0));
        }
    }
    data.clear();

    //initialize probabilities
    probability.push_back(0);
    for (int j = 0; j < alph_size; j++) {
        probability.push_back(probability[j] + ((N - 2) * (freq[j] + 1) / decoded_string_size));
    }
    for (int j = 0; j < alph_size + 1; j++) {
        probability[j] = probability[j] * (N - 2) / probability[alph_size];
    }

    int begin = 0;
    unsigned long long block = 0;
    for (int i = 0; i < kBinaryBlockSize; i++) {
        if (i > bit_data.size()) {
            block = block * 2;
        }
        else {
            block = block | (1 << (kBinaryBlockSize - 1 - i)) * bit_data[i];
        }
    }

    while (decoded_string.size() < decoded_string_size) {
        int symbol = 0;
        int left_binary = 0, right_binary = alph_size + 1;
        while (right_binary - left_binary != 1) {
            int middleBinary = (right_binary + left_binary) / 2;
            unsigned long long symbolLeft = left + (((right - left + 1) * probability[middleBinary]) >> kBinaryBlockSize);
            if (block >= symbolLeft) {
                left_binary = middleBinary;
            }
            else {
                right_binary = middleBinary;
            }
        }
        symbol = right_binary - 1;

        long long prev_left = left;
        left = prev_left + (((right - prev_left + 1) * probability[symbol]) >> kBinaryBlockSize);
        right = prev_left + (((right - prev_left + 1) * probability[symbol + 1]) >> kBinaryBlockSize);
        decoded_string.add(symbol);
        while ((left >> (kBinaryBlockSize - 1)) == (right >> (kBinaryBlockSize - 1))) {
            begin++;
            if (begin - 1 < bit_data.size()) {
                block -= ((1 << (kBinaryBlockSize - 1)) * bit_data[begin - 1]);
            }
            block = block << 1;
            if (begin + kBinaryBlockSize - 1 < bit_data.size()) {
                block = block | bit_data[kBinaryBlockSize - 1 + begin];
            }
            left = left % MOD * 2;
            right = (right % MOD - 1) * 2;
        }

        if (right - left < EPS) {
            for (int i = 0; i < kBinaryBlockSize - kEpsSize; i++) {
                begin++;
                if (begin - 1 < bit_data.size()) {
                    block = block - ((1 << (kBinaryBlockSize - 1)) * bit_data[begin - 1]);
                }
                block = block << 1;
                if (begin + kBinaryBlockSize - 1 < bit_data.size()) {
                    block = block | bit_data[kBinaryBlockSize - 1 + begin];
                }
                left = (left % MOD) * 2;
            }
            while (left / MOD == 1) {
                begin++;
                if (begin - 1 < bit_data.size()) {
                    block = block - ((1 << (kBinaryBlockSize - 1)) * bit_data[begin - 1]);
                }
                block = block << 1;
                if (begin + kBinaryBlockSize - 1 < bit_data.size()) {
                    block = block | bit_data[kBinaryBlockSize - 1 + begin];
                }
                left = (left % MOD) * 2;
            }
            right = N - 1;
        }
    }

    std::swap(data, decoded_string);
}
