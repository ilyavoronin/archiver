#include "gtest/gtest.h"
#include "AString.h"

TEST(StringTests, testArraySubscriptOpearator) {
    String <mchar> s(10);

    for (int i = 0; i < 10; i++) {
        s[i] = 'a' + i;
    }

    for (int i = 0; i < 10; i++) {
        ASSERT_EQ(s[i], 'a' + i);
    }
}

TEST(StringTests, testAdd) {
    String <mchar> s(0);

    for (int i = 0; i < 10; i++) {
        s.add(mchar('a' + i));
    }

    for (int i = 0; i < 10; i++) {
        ASSERT_EQ(s[i], 'a' + i);
    }
}

TEST(StringTests, testPlusCharOperator) {
    String <mchar> s(0);

    for (int i = 0; i < 10; i++) {
        s = s + mchar('a' + i);
    }

    for (int i = 0; i < 10; i++) {
        ASSERT_EQ(s[i], 'a' + i);
    }
}

TEST(StringTests, testPlusEqCharOperator) {
    String <mchar> s(0);

    for (int i = 0; i < 10; i++) {
        s += mchar('a' + i);
    }

    for (int i = 0; i < 10; i++) {
        ASSERT_EQ(s[i], 'a' + i);
    }
}

TEST(StringTests, testPlusOperator) {
    String <mchar> s1(10), s2(10);
    for (int i = 0; i < 10; i++) {
        s1[i] = mchar('a' + i);
    }
    for (int j = 0; j < 10; j++) {
        s2[j] = mchar('a' + 10 + j);
    }

    String res = s1 + s2;
    std::string expected = "abcdefghijklmnopqrst";

    for (int i = 0; i < 20; i++) {
        ASSERT_EQ(res[i], expected[i]);
    }
}

TEST(StringTests, testPlusEqOperator) {
    String <mchar> s1(10), s2(10);
    for (int i = 0; i < 10; i++) {
        s1[i] = mchar('a' + i);
    }
    for (int j = 0; j < 10; j++) {
        s2[j] = mchar('a' + 10 + j);
    }

    s1 += s2;
    std::string expected = "abcdefghijklmnopqrst";

    for (int i = 0; i < 20; i++) {
        ASSERT_EQ(s1[i], expected[i]);
    }
}

TEST(StringTests, testSize) {
    String <mchar> s(10);

    ASSERT_EQ(s.size(), 10);
}

TEST(StringTests, testClear) {
    String <mchar> s(10);

    s.clear();

    ASSERT_EQ(s.size(), 0);
}

TEST(StringTests, testResize) {
    String <mchar> s(10);

    s.resize(20);

    ASSERT_EQ(s.size(), 20);
}

TEST(BoolStringTests, testConstructor) {
    String <bool> s(20);

    ASSERT_EQ(s.size(), 20);
}

TEST(BoolStringTests, testAddOperator) {
    String <bool> s;
    std::vector <bool> a = {1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1};

    for (int i = 0; i < a.size(); i++) {
        s.add(a[i]);
    }

    for (int i = 0; i < a.size(); i++) {
        ASSERT_EQ(s[i], a[i]);
    }
}

TEST(BoolStringTests, testAddEqOperator) {
    String <bool> s;
    std::vector <bool> a = {1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1};

    for (int i = 0; i < a.size(); i++) {
        s += a[i];
    }

    for (int i = 0; i < a.size(); i++) {
        ASSERT_EQ(s[i], a[i]);
    }
}

TEST(BoolStringTests, testAddStringOperator) {
    std::vector <bool> s1v = {1, 0, 1, 1, 1, 0};
    std::vector <bool> s2v = {1, 1, 0, 0, 0, 0, 1, 1};
    String <bool> s1(s1v);
    String <bool> s2(s2v);

    String <bool> s = s1 + s2;
    std::vector <bool> expected = {1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1};

    for (int i = 0; i < expected.size(); i++) {
        ASSERT_EQ(s[i], expected[i]);
    }
}

TEST(BoolStringTests, testAddEqStringOperator) {
    std::vector <bool> s1v = {1, 0, 1, 1, 1, 0};
    std::vector <bool> s2v = {1, 1, 0, 0, 0, 0, 1, 1};
    String <bool> s(s1v);
    String <bool> s2(s2v);

    s += s2;
    std::vector <bool> expected = {1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1};

    for (int i = 0; i < expected.size(); i++) {
        ASSERT_EQ(s[i], expected[i]);
    }
}

TEST(BoolStringTests, testEqOperatorFalse) {
    std::vector <bool> s1v = {1, 0, 1, 1, 1, 0};
    std::vector <bool> s2v = {1, 0, 1, 1, 1, 0, 0};
    String <bool> s1(s1v);
    String <bool> s2(s2v);

    ASSERT_FALSE(s1v == s2v);
}

TEST(BoolStringTests, testEqOperatorTrue) {
    std::vector <bool> s1v = {1, 0, 1, 1, 1, 0};
    std::vector <bool> s2v = {1, 0, 1, 1, 1, 0};
    String <bool> s1(s1v);
    String <bool> s2(s2v);

    ASSERT_TRUE(s1v == s2v);
}

TEST(BoolStringTests, testSet0) {
    std::vector <bool> s1v = {1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1};
    String <bool> s(s1v);

    s.set(12, 0);

    ASSERT_EQ(s[12], 0);
}

TEST(BoolStringTests, testSet1) {
    std::vector <bool> s1v = {1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1};
    String <bool> s(s1v);

    s.set(1, 1);

    ASSERT_EQ(s[1], 1);
}

TEST(BoolStringTests, testResize) {
    std::vector <bool> s1v = {1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1};
    String <bool> s(s1v);

    s.resize(5);
    std::vector <bool> expected = {1, 0, 1, 1, 1};

    ASSERT_EQ(s.size(), 5);
    for (int i = 0; i < 5; i++) {
        ASSERT_EQ(s[i], expected[i]);
    }
    for (int i = 5; i < 8; i++) {
        ASSERT_EQ(s[i], 0);
    }
}