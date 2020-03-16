#include "gtest/gtest.h"
#include "RLE2.h"

TEST(RLE2Tests, testEncode) {
    String <mchar> data({'a', 'a', 'a', 'b', 'c', 'd', 'd'});
    DataInfo di;

    RLE2().encode(data, di);
    String <mchar> expected({0, 0, 1, 0, 'a', 1, 'b', 1, 'c', 0, 1, 'd'});

    ASSERT_EQ(data, expected);
}

TEST(RLE2Tests, testDecode) {
    String <mchar> data({0, 0, 1, 0, 'a', 1, 'b', 1, 'c', 0, 1, 'd'});
    DataInfo di;

    RLE2().decode(data, di);
    String <mchar> expected({'a', 'a', 'a', 'b', 'c', 'd', 'd'});

    ASSERT_EQ(data, expected);
}

TEST(RLE2Tests, testEncodeDecode) {
    String <mchar> data;
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
    String <mchar> expected = data;

    RLE2().encode(data, di);
    RLE2().decode(data, di);

    ASSERT_EQ(data, expected);
}