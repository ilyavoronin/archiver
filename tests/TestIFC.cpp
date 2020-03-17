#include "gtest/gtest.h"

#include "IFC.h"

TEST(IFCTests, testIFCEncodeDecodeSmall) {
    String <mchar> data({0, 1, 0, 2, 3, 4, 5, 6, 8, 1, 1, 1, 2, 2, 1, 1, 2});
    DataInfo di;
    auto expected = data;

    IFC().encode(data, di);
    IFC().decode(data, di);

    ASSERT_EQ(data, expected);
}

TEST(IFCTests, testIFCEncodeDecodeBig) {
    srand(17);
    String <mchar> data({0, 1, 0, 2, 3, 4, 5, 6, 8, 1, 1, 1, 2, 2, 1, 1, 2});
    for (int i = 0; i < 100000; i++) {
        if (rand() % 3 < 2) {
            data.add(data.back());
            continue;
        }
        data.add(rand());
    }
    DataInfo di;
    auto expected = data;

    IFC().encode(data, di);
    IFC().decode(data, di);

    ASSERT_EQ(data, expected);
}

TEST(IFCTests, testIFCEncodeDecodeBigRand) {
    srand(17);
    String <mchar> data({0, 1, 0, 2, 3, 4, 5, 6, 8, 1, 1, 1, 2, 2, 1, 1, 2});
    for (int i = 0; i < 100000; i++) {
        data.add(rand());
    }
    DataInfo di;
    auto expected = data;

    IFC().encode(data, di);
    IFC().decode(data, di);

    ASSERT_EQ(data, expected);
}