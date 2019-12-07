#include "gtest/gtest.h"
#include "SuffixSort.h"

TEST(SuffixSortTests, testSort) {
    std::vector <char> vdata = {'a', 'b', 'a', 'c', 'a', 'b', 'a', char(255)};
    String <Symbol> data;
    for (auto z : vdata) {
        data.add(z);
    }
    String <int> sorted_suffixes;

    SuffixSort().sort(data, sorted_suffixes);
    std::vector <int> expected = {0, 4, 2, 6, 1, 5, 3, 7};

    for (int i = 0; i < 8; i++) {
        ASSERT_EQ(sorted_suffixes[i], expected[i]);
    }
}