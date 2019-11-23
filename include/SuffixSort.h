#ifndef ARCHIVER_SUFFIXSORT_H
#define ARCHIVER_SUFFIXSORT_H

#include "AString.h"


class SuffixSort {
private:
    void qsort(String <Symbol> &data, String <int> &sortedSuffixes, int L, int R);
    bool cmp(int i, int j, String <Symbol> &data);
public:
    void sort(String <Symbol> &data, String <int> &sortedSuffixes);
};


#endif //ARCHIVER_SUFFIXSORT_H
