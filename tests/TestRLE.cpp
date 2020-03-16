#include "gtest/gtest.h"

#include "RLE.h"

#include "AString.h"

TEST(RLETests, testEncode) {
    String <mchar> data({'a', 'a', 'b', 'c', 'a', 'a', 'a', 'a'});
    String <mchar> expected({'a', 'a', (char)128, 'b', 'c', 'a', 'a', (char)130});
    DataInfo di;

    RLE().encode(data, di);

    ASSERT_EQ(data, expected);
}

TEST(RLETests, testDecode) {
    String <mchar> data({'a', 'a', (char)128, 'b', 'c', 'a', 'a', (char)130});
    String <mchar> expected({'a', 'a', 'b', 'c', 'a', 'a', 'a', 'a'});
    DataInfo di;

    RLE().decode(data, di);

    ASSERT_EQ(data, expected);
}

TEST(RLETests, testEncodeDecodeSmall) {
    String <mchar> data({'a', 'a', 'b', 'c', 'a', 'a', 'a', 'a'});
    String <mchar> expected = data;
    DataInfo di;

    RLE().encode(data, di);
    RLE().decode(data, di);

    ASSERT_EQ(data, expected);
}

TEST(RLETests, testEncodeDecodeBig) {
    String <mchar> data({'a', 'b', 'c', 'c', 'c', 'a', 'a', 'd'});
    for (int i = 0; i < 10000; i++) {
        data.add('z');
    }
    for (int i = 0; i < 500; i++) {
        data.add('t');
    }
    for (int i = 0; i < 130; i++) {
        data.add('y');
    }
    data.add('z');
    String <mchar> expected = data;
    DataInfo di;

    RLE().encode(data, di);
    RLE().decode(data, di);

    ASSERT_EQ(data, expected);
}