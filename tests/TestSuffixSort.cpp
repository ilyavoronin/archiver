#include "gtest/gtest.h"
#include "SuffixSort.h"

TEST(SuffixSortTests, testSort1) {
    std::vector <char> vdata = {'a', 'b', 'a', 'c', 'a', 'b', 'a'};
    String <Symbol> data;
    for (auto z : vdata) {
        data.add(z);
    }
    String <int> sorted_suffixes;

    SuffixSort().sort(data, sorted_suffixes);
    std::vector <int> expected = {7, 6, 4, 0, 2, 5, 1, 3};

    for (int i = 0; i < expected.size(); i++) {
        ASSERT_EQ(sorted_suffixes[i], expected[i]);
    }
}

TEST(SuffixSortTests, testSort2) {
    std::vector <char> vdata = {'a', 'c', 'c', 'b', 'c', 'b', 'c', 'b', 'c', 'b', 'a', 'b', 'b', 'c'};
    String <Symbol> data;
    for (auto z : vdata) {
        data.add(z);
    }
    String <int> sorted_suffixes;

    SuffixSort().sort(data, sorted_suffixes);
    std::vector <int> expected = {14, 10, 0, 9, 11, 12, 7, 5, 3, 13, 8, 6, 4, 2, 1};

    for (int i = 0; i < expected.size(); i++) {
        ASSERT_EQ(sorted_suffixes[i], expected[i]);
    }
}