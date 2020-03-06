#include "gtest/gtest.h"
#include "RLE2.h"

TEST(RLE2Tests, testEncode) {
    String <Symbol> data({'a', 'a', 'a', 'b', 'c', 'd', 'd'});
    DataInfo di;

    RLE2().encode(data, di);
    String <Symbol> expected({0, 0, 1, 0, 'a', 1, 'b', 1, 'c', 0, 1, 'd'});

    ASSERT_EQ(data, expected);
}

TEST(RLE2Tests, testDecode) {
    String <Symbol> data({0, 0, 1, 0, 'a', 1, 'b', 1, 'c', 0, 1, 'd'});
    DataInfo di;

    RLE2().decode(data, di);
    String <Symbol> expected({'a', 'a', 'a', 'b', 'c', 'd', 'd'});

    ASSERT_EQ(data, expected);
}

TEST(RLE2Tests, testEncodeDecode) {
    String <Symbol> data;
    DataInfo di;
    for (int i = 0; i < 256; i++) {
        char c = i;
        for (int j = 0; j < i + 1; j++) {
            data += c;
        }
    }
    for (int i = 0; i < 1060; i++) {
        data += i;
    }
    String <Symbol> expected = data;

    RLE2().encode(data, di);
    RLE2().decode(data, di);

    ASSERT_EQ(data, expected);
}