#include "gtest/gtest.h"
#include "BWT.h"

TEST(BWTTests, testEncode) {
    std::vector <char> vdata = {'a', 'b', 'a', 'c', 'a', 'b', 'a'};
    DataInfo data_info;
    String <mchar> data;
    for (auto z : vdata) {
        data.add(z);
    }

    std::vector <char> expected = {'a', 'b', 'c', 0, 'b', 'a', 'a', 'a'};
    BWT().encode(data, data_info);

    for (int i = 0; i < 8; i++) {
        ASSERT_EQ(data[i], expected[i]);
    }
    int first_suffix_number;
    data_info.read(first_suffix_number);
    ASSERT_EQ(first_suffix_number, 3);
}

TEST(BWTTests, testDecode) {
    std::vector <char> vdata = {'a', 'b', 'c', 0, 'b', 'a', 'a', 'a'};
    DataInfo data_info;

    //first suffix number
    data_info.write((int)3);
    String <mchar> data;
    for (auto z : vdata) {
        data.add(z);
    }

    std::vector <char> expected = {'a', 'b', 'a', 'c', 'a', 'b', 'a'};
    BWT().decode(data, data_info);

    for (int i = 0; i < 7; i++) {
        ASSERT_EQ(data[i], expected[i]);
    }
}

TEST(BWTTests, testEncodeDecode) {
    srand(17);
    DataInfo data_info;
    String <mchar> data(1000);
    for (int i = 0; i < 1000; i++) {
        data[i] = mchar((char)(rand() % 256));
    }

    String <mchar> data_copy = data;
    BWT().encode(data, data_info);
    BWT().decode(data, data_info);

    ASSERT_EQ(data, data_copy);
}