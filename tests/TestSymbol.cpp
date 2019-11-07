#include "gtest/gtest.h"
#include "Symbol.h"

TEST(SymbolTests, testToChar) {
    Symbol c(255);

    char actual = c.toChar();
    char expected = char(255);

    ASSERT_EQ(actual, expected);
}

TEST(SymbolTests, testGet) {
    Symbol c(255);

    int actual = c.get();
    int expected = 255;

    ASSERT_LE(actual, expected);
}

TEST(SymbolTests, testLE) {
    Symbol c1(200), c2(201);

    ASSERT_TRUE(c1 < c2);
}