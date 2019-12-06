#include "gtest/gtest.h"

#include "String.h"
#include "MTF.h"

TEST(MTFTests, testEncode) {
    std::string sdata = "abacabadaca";
    int n = sdata.size();
    String <Symbol> data;
    for (int i = 0; i < n; i++) {
        data.add(sdata[i]);
    }

    MTF().encode(data);
    std::vector <int> expected = {(int)'a', (int)'b', 1, (int)'c', 1, 2, 1, (int)'d', 1, 3, 1};

    for (int i = 0; i < n; i++) {
        ASSERT_EQ(data[i].get(), expected[i]) << "at position " << i;
    }
}

TEST(MTFTests, testDecode) {
    std::vector <int> vdata = {(int)'a', (int)'b', 1, (int)'c', 1, 2, 1, (int)'d', 1, 3, 1};
    int n = vdata.size();
    String <Symbol> data;
    for (int i = 0; i < n; i++) {
        data.add(vdata[i]);
    }

    MTF().decode(data);
    std::string expected = "abacabadaca";

    for (int i = 0; i < n; i++) {
        ASSERT_EQ(data[i].get(), expected[i]) << "at position " << i;
    }
}

TEST(MTFTests, testEncodeDecode) {
    srand(17);
    String <Symbol> data;
    for (int i = 0; i < 2; i++) {
        data.add(rand() % 256);
    }

    String <Symbol> dataCopy = data;
    MTF().encode(data);
    MTF().decode(data);

    ASSERT_EQ(data, dataCopy);
}