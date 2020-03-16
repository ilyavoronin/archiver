#include "gtest/gtest.h"

#include "RLE.h"

#include "AString.h"

TEST(RLETests, testEncode) {
    String <Symbol> data({'a', 'a', 'b', 'c', 'a', 'a', 'a', 'a'});
    String <Symbol> expected({'a', 'a', (char)128, 'b', 'c', 'a', 'a', (char)130});
    DataInfo di;

    RLE().encode(data, di);

    ASSERT_EQ(data, expected);
}

TEST(RLETests, testDecode) {
    String <Symbol> data({'a', 'a', (char)128, 'b', 'c', 'a', 'a', (char)130});
    String <Symbol> expected({'a', 'a', 'b', 'c', 'a', 'a', 'a', 'a'});
    DataInfo di;

    RLE().decode(data, di);

    ASSERT_EQ(data, expected);
}

TEST(RLETests, testEncodeDecodeSmall) {
    String <Symbol> data({'a', 'a', 'b', 'c', 'a', 'a', 'a', 'a'});
    String <Symbol> expected = data;
    DataInfo di;

    RLE().encode(data, di);
    RLE().decode(data, di);

    ASSERT_EQ(data, expected);
}

TEST(RLETests, testEncodeDecodeBig) {
    String <Symbol> data({'a', 'b', 'c', 'c', 'c', 'a', 'a', 'd'});
    for (int i = 0; i < 10000; i++) {
        data.add('z');
    }
    for (int i = 0; i < 500; i++) {
        data.add('t');
    }
    data.add('z');
    String <Symbol> expected = data;
    DataInfo di;

    RLE().encode(data, di);
    RLE().decode(data, di);

    ASSERT_EQ(data, expected);
}