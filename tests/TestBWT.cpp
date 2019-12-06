#include "gtest/gtest.h"
#include "BWT.h"

TEST(BWTTests, testEncode) {
    std::vector <char> vdata = {'a', 'b', 'a', 'c', 'a', 'b', 'a'};
    DataInfo data_info;
    String <Symbol> data;
    for (auto z : vdata) {
        data.add(z);
    }

    std::vector <char> expected = {char(255), 'c', 'b', 'b', 'a', 'a', 'a', 'a'};
    BWT().encode(data, data_info);

    for (int i = 0; i < 8; i++) {
        ASSERT_EQ(data[i].toChar(), expected[i]);
    }
    int first_suffix_number;
    data_info.read(first_suffix_number);
    ASSERT_EQ(first_suffix_number, 0);
}

TEST(BWTTests, testDecode) {
    std::vector <char> vdata = {char(255), 'c', 'b', 'b', 'a', 'a', 'a', 'a'};
    DataInfo data_info;
    data_info.write((int)0);
    String <Symbol> data;
    for (auto z : vdata) {
        data.add(z);
    }

    std::vector <char> expected = {'a', 'b', 'a', 'c', 'a', 'b', 'a'};
    BWT().decode(data, data_info);

    for (int i = 0; i < 7; i++) {
        ASSERT_EQ(data[i].toChar(), expected[i]);
    }
}

TEST(BWTTests, testEncodeDecode) {
    srand(17);
    DataInfo data_info;
    String <Symbol> data(1000);
    for (int i = 0; i < 1000; i++) {
        data[i] = Symbol((char)(rand() % 256));
    }

    String <Symbol> data_copy = data;
    BWT().encode(data, data_info);
    BWT().decode(data, data_info);

    ASSERT_EQ(data, data_copy);
}