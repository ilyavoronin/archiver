#include "gtest/gtest.h"
#include "AString.h"

TEST(StringTests, testArraySubscriptOpearator) {
    String <Symbol> s(10);

    for (int i = 0; i < 10; i++) {
        s[i] = 'a' + i;
    }

    for (int i = 0; i < 10; i++) {
        ASSERT_EQ(s[i].toChar(), 'a' + i);
    }
}

TEST(StringTests, testAdd) {
    String <Symbol> s(0);

    for (int i = 0; i < 10; i++) {
        s.add(Symbol('a' + i));
    }

    for (int i = 0; i < 10; i++) {
        ASSERT_EQ(s[i].toChar(), 'a' + i);
    }
}

TEST(StringTests, testPlusCharOperator) {
    String <Symbol> s(0);

    for (int i = 0; i < 10; i++) {
        s = s + Symbol('a' + i);
    }

    for (int i = 0; i < 10; i++) {
        ASSERT_EQ(s[i].toChar(),'a' + i);
    }
}

TEST(StringTests, testPlusEqCharOperator) {
    String <Symbol> s(0);

    for (int i = 0; i < 10; i++) {
        s += Symbol('a' + i);
    }

    for (int i = 0; i < 10; i++) {
        ASSERT_EQ(s[i].toChar(), 'a' + i);
    }
}

TEST(StringTests, testPlusOperator) {
    String <Symbol> s1(10), s2(10);
    for (int i = 0; i < 10; i++) {
        s1[i] = Symbol('a' + i);
    }
    for (int j = 0; j < 10; j++) {
        s2[j] = Symbol('a' + 10 + j);
    }

    String res = s1 + s2;
    std::string expected = "abcdefghijklmnopqrst";

    for (int i = 0; i < 20; i++) {
        ASSERT_EQ(res[i].toChar(), expected[i]);
    }
}

TEST(StringTests, testPlusEqOperator) {
    String <Symbol> s1(10), s2(10);
    for (int i = 0; i < 10; i++) {
        s1[i] = Symbol('a' + i);
    }
    for (int j = 0; j < 10; j++) {
        s2[j] = Symbol('a' + 10 + j);
    }

    s1 += s2;
    std::string expected = "abcdefghijklmnopqrst";

    for (int i = 0; i < 20; i++) {
        ASSERT_EQ(s1[i].toChar(), expected[i]);
    }
}

TEST(StringTests, testSize) {
    String <Symbol> s(10);

    ASSERT_EQ(s.size(), 10);
}

TEST(StringTests, testClear) {
    String <Symbol> s(10);

    s.clear();

    ASSERT_EQ(s.size(), 0);
}

TEST(StringTests, testResize) {
    String <Symbol> s(10);

    s.resize(20);

    ASSERT_EQ(s.size(), 20);
}