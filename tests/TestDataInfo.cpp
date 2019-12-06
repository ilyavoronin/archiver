#include "gtest/gtest.h"

#include "DataInfo.h"

#include <string>
#include <cstdio>

#include "Reader.h"
#include "Writer.h"

TEST(DataInfoTests, testWriteReadShort) {
    DataInfo d;

    short int expected1 = 2000, expected2 = 3000;
    d.write(expected1);
    d.write(expected2);
    short int actual1, actual2;
    d.read(actual1);
    d.read(actual2);

    ASSERT_EQ(actual1, expected1);
    ASSERT_EQ(actual2, expected2);
}

TEST(DataInfoTests, testWriteReadInt) {
    DataInfo d;

    int expected1 = 100000000, expected2 = 100000000;
    d.write(expected1);
    d.write(expected2);
    int actual1, actual2;
    d.read(actual1);
    d.read(actual2);

    ASSERT_EQ(actual1, expected1);
    ASSERT_EQ(actual2, expected2);
}

TEST(DataInfoTests, testWriteReadSymbol) {
    DataInfo d;

    Symbol expected1('a'), expected2('b');
    d.write(expected1);
    d.write(expected2);
    Symbol actual1, actual2;
    actual1 = d.read();
    actual2 = d.read();

    ASSERT_EQ(actual1.toChar(), expected1.toChar());
    ASSERT_EQ(actual2.toChar(), expected2.toChar());
}

TEST(DataInfoTests, testWriteReadSymbolString) {
    DataInfo d;

    String <Symbol> expected1(10), expected2(10);
    for (int i = 0; i < 10; i++) {
        expected1[i] = 'a' + i;
        expected2[i] = 'j' + i;
    }
    d.write(expected1);
    d.write(expected2);
    String <Symbol> actual1, actual2;
    d.read(actual1);
    d.read(actual2);

    ASSERT_EQ(actual1, expected1);
    ASSERT_EQ(actual2, expected2);
}

TEST(DataInfoTests, testWriteReadBoolString) {
    DataInfo d;

    String <Symbol> expected1(10), expected2(10);
    for (int i = 0; i < 10; i++) {
        expected1[i] = i % 2;
        expected2[i] = (i % 2) ^ 1;
    }
    d.write(expected1);
    d.write(expected2);
    String <Symbol> actual1, actual2;
    d.read(actual1);
    d.read(actual2);

    ASSERT_EQ(actual1, expected1);
    ASSERT_EQ(actual2, expected2);
}

TEST(DataInfoTests, testWriteReadToFile) {
    DataInfo d, d2;

    std::string tmp_file_name = "a.tmp";
    String <Symbol> expected1(10);
    for (int i = 0; i < 10; i++) {
        expected1[i] = 'a' + i;
    }
    int expected2 = 2000;
    d.write(expected1);
    d.write(expected2);
    Writer writer(tmp_file_name, 100, Writer::Mode::BIN);
    d.writeToFile(writer);
    writer.close();
    Reader reader(tmp_file_name, 100, Reader::Mode::BIN);
    d2.readFromFile(reader);
    String <Symbol> actual1;
    int actual2;
    d2.read(actual1);
    d2.read(actual2);
    remove(tmp_file_name.c_str());

    ASSERT_EQ(actual1, expected1);
    ASSERT_EQ(actual2, expected2);
}