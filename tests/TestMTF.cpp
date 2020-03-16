#include "gtest/gtest.h"
#include "MTF.h"

#include "AString.h"

TEST(MTFTests, testEncode) {
    std::string sdata = "abacabadaca";
    int n = sdata.size();
    String <mchar> data;
    for (int i = 0; i < n; i++) {
        data.add(sdata[i]);
    }

    DataInfo di = DataInfo();
    MTF().encode(data, di);
    std::vector <int> expected = {(int)'a', (int)'b', 1, (int)'c', 1, 2, 1, (int)'d', 1, 3, 1};

    for (int i = 0; i < n; i++) {
        ASSERT_EQ(data[i], expected[i]) << "at position " << i;
    }
}

TEST(MTFTests, testDecode) {
    std::vector <int> vdata = {(int)'a', (int)'b', 1, (int)'c', 1, 2, 1, (int)'d', 1, 3, 1};
    int n = vdata.size();
    String <mchar> data;
    for (int i = 0; i < n; i++) {
        data.add(vdata[i]);
    }

    DataInfo di = DataInfo();
    MTF().decode(data, di);
    std::string expected = "abacabadaca";

    for (int i = 0; i < n; i++) {
        ASSERT_EQ(data[i], expected[i]) << "at position " << i;
    }
}

TEST(MTFTests, testEncodeDecode) {
    srand(17);
    String <mchar> data;
    for (int i = 0; i < 2; i++) {
        data.add(rand() % 256);
    }

    String <mchar> data_copy = data;
    DataInfo di = DataInfo();
    MTF().encode(data, di);
    MTF().decode(data, di);

    ASSERT_EQ(data, data_copy);
}