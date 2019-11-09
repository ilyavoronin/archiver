#include "gtest/gtest.h"

#include "AString.h"
#include "HuffmanTree.h"

#include <map>
#include <cmath>

class HuffmanTreeTests : public ::testing::Test {
protected:
    String <Symbol> s{1000};
    HuffmanTree *ht;
    void SetUp() override {
        int i = 0;
        for (; i < 400; i++) {
            s[i] = 'a';
        }
        for (; i < 600; i++) {
            s[i] = 'b';
        }
        for (; i < 1000; i++) {
            s[i] = 'a' + (i % 26);
        }
        ht = new HuffmanTree(s);
    }

    bool is_prefix(String <bool> &s1, String <bool> &s2) {
        if (s1.size() > s2.size()) {
            return false;
        }
        for (int i = 0; i < (int)s1.size(); i++) {
            if (s1[i] != s2[i]) {
                return false;
            }
        }
        return true;
    }
};

TEST_F(HuffmanTreeTests, testGetCodesCheckOptimum) {
    std::map <Symbol, String <bool> > codes = ht->getCodes();
    long double actual = 0;
    for (auto &p : codes) {
        actual += pow(2, -p.second.size());
    }

    ASSERT_NEAR(actual, 1, 0.01);
}

TEST_F(HuffmanTreeTests, testGetCodesCheckPrefix) {
    std::map <Symbol, String <bool> > codes = ht->getCodes();
    long double actual = 0;
    std::vector <String <bool> > vcodes;
    for (auto &p : codes) {
        vcodes.push_back(p.second);
    }

    for (int j = 0; j < (int)vcodes.size(); j++) {
        for (int k = 0; k < (int)vcodes.size(); k++) {
            if (j != k) {
                if (is_prefix(vcodes[j], vcodes[k])) {
                    FAIL() << "Two codes have common prefix\n";
                }
            }
        }
    }
}

TEST_F(HuffmanTreeTests, testWriteReadTree) {
    DataInfo d;

    ht->writeTree(d);
    HuffmanTree ht2;
    ht2.readTree(d);
    auto m1 = ht->getCodes();
    auto m2 = ht2.getCodes();

    for (auto elem : m1) {
        ASSERT_EQ(m2[elem.first], elem.second);
    }
}

TEST_F(HuffmanTreeTests, testGetNextSymbol) {
    String <bool> bs;
    auto codes = ht->getCodes();
    for (auto elem : codes) {
        bs += elem.second;
    }

    int i = 0;
    for (auto elem : codes) {
        ASSERT_EQ(elem.first, ht->getNextSymbol(bs, i));
    }
}