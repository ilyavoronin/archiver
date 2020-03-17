#include "gtest/gtest.h"

#include "ArithmeticCoding.h"

TEST(ArithmeticCodingTests, testEncodeDecode) {
    String <mchar> data({'a', 'b', 'c', 'd', 'a', 'a', 'a', 'd', 'd', 'a', 'a', 'a'});
    DataInfo di;
    String <mchar> expected = data;

    ArithmeticCoding().encode(data, di);
    ArithmeticCoding().decode(data, di);

    ASSERT_EQ(data, expected);
}

TEST(ArithmeticCodingTests, testEncodeDecodeBig) {
    srand(17);
    String <mchar> data({'a', 'b', 'c', 'd', 'a', 'a', 'a', 'd', 'd', 'a', 'a', 'a'});
    for (int i = 0; i < 10000; i++) {
        data.add(rand() % 256);
    }
    for (int i = 0; i < 10000; i++) {
        data.add('z');
    }
    for (int i = 0; i < 10000; i++) {
        data.add('a' + rand() % 26);
    }
    for (int i = 0; i < 10000; i++) {
        data.add('c' + rand() % 3);
    }
    data.add('v');
    data.add('y');
    String <mchar> expected = data;
    DataInfo di;

    ArithmeticCoding().encode(data, di);
    ArithmeticCoding().decode(data, di);

    ASSERT_EQ(data, expected);
}

TEST(ArithmeticCodingTests, testBinaryEncodeDecodeBig) {
    srand(17);
    String <bool> data;
    for (int i = 0; i < 10000; i++) {
        data.add(rand() % 2);
    }
    for (int i = 0; i < 10000; i++) {
        data.add(0);
    }
    for (int i = 0; i < 10000; i++) {
        data.add(rand() % 2);
    }
    for (int i = 0; i < 10000; i++) {
        data.add(1);
    }
    data.add(0);
    String <bool> expected = data;
    DataInfo di;

    ArithmeticCoding().encodeBinary(data, di);
    ArithmeticCoding().decodeBinary(data, di);

    ASSERT_EQ(data, expected);
}