#include "gtest/gtest.h"
#include "BWT.h"

TEST(BWTTests, testEncode) {
    std::vector <char> vdata = {'a', 'b', 'a', 'c', 'a', 'b', 'a'};
    DataInfo dataInfo;
    String <Symbol> data;
    for (auto z : vdata) {
        data.add(z);
    }

    std::vector <char> expected = {char(255), 'c', 'b', 'b', 'a', 'a', 'a', 'a'};
    BWT().encode(data, dataInfo);

    for (int i = 0; i < 8; i++) {
        ASSERT_EQ(data[i].toChar(), expected[i]);
    }
    int firstSuffixNumber;
    dataInfo.read(firstSuffixNumber);
    ASSERT_EQ(firstSuffixNumber, 0);
}

TEST(BWTTests, testDecode) {
    std::vector <char> vdata = {char(255), 'c', 'b', 'b', 'a', 'a', 'a', 'a'};
    DataInfo dataInfo;
    dataInfo.write((int)0);
    String <Symbol> data;
    for (auto z : vdata) {
        data.add(z);
    }

    std::vector <char> expected = {'a', 'b', 'a', 'c', 'a', 'b', 'a'};
    BWT().decode(data, dataInfo);

    for (int i = 0; i < 7; i++) {
        ASSERT_EQ(data[i].toChar(), expected[i]);
    }
}

TEST(BWTTests, testEncodeDecode) {
    srand(17);
    DataInfo dataInfo;
    String <Symbol> data(1000);
    for (int i = 0; i < 1000; i++) {
        data[i] = Symbol((char)(rand() % 256));
    }

    String <Symbol> dataCopy = data;
    BWT().encode(data, dataInfo);
    BWT().decode(data, dataInfo);

    ASSERT_EQ(data, dataCopy);
}