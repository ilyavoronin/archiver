#include "gtest/gtest.h"
#include "RLE2.h"
#include "ArithmeticCoding.h"

TEST(RLE2Tests, testEncode) {
    String <mchar> data({'a', 'a', 'a', 'b', 'c', 'd', 'd'});
    DataInfo di;

    RLE2().encode(data, di);
    String <mchar> expected({'a', 'b', 'c', 'd'});
    String <bool> expected_runs({0, 0, 1, 0, 1, 1, 0, 1});
    DataInfo di1;
    ArithmeticCoding().encodeBinary(expected_runs, di1);
    String <bool> runs;
    di.read(runs);

    ASSERT_EQ(data, expected);
    ASSERT_EQ(runs, expected_runs);
}

TEST(RLE2Tests, testDecode) {
    String <mchar> data({'a', 'b', 'c', 'd'});
    String <bool> runs({0, 0, 1, 0, 1, 1, 0, 1});
    DataInfo di;
    ArithmeticCoding().encodeBinary(runs, di);
    di.beginNewBlock();
    di.write(runs);

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