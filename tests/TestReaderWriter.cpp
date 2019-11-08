#include "gtest/gtest.h"
#include "Reader.h"
#include "Writer.h"
#include <string>

TEST(IOTests, testWriteReadInt) {
    std::string tmpFileName = "f.tmp";
    Reader reader(tmpFileName, 100, Reader::Mode::BIN);
    Writer writer(tmpFileName, 100, Writer::Mode::BIN);

    int expected = 100000000;
    writer.write(expected);
    writer.close();
    int actual;
    reader.read(actual);

    ASSERT_EQ(actual, expected);
}

TEST(IOTests, testsWriteReadSymbolString) {
    std::string tmpFileName = "f.tmp";
    Reader reader(tmpFileName, 100, Reader::Mode::BIN);
    Writer writer(tmpFileName, 100, Writer::Mode::BIN);

    String <Symbol> expected(10);
    for (int i = 0; i < 10; i++) {
        expected[i] = Symbol(i);
    }
    writer.write(expected);
    writer.close();
    String <Symbol> actual;
    reader.read(actual, 10);

    ASSERT_EQ(actual, expected);
}