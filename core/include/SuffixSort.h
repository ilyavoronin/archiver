#ifndef ARCHIVER_SUFFIXSORT_H
#define ARCHIVER_SUFFIXSORT_H

#include "AString.h"


class SuffixSort {
  public:
    void sort(String <Symbol> &data, String <int> &sorted_suffixes);
    
  private:
    void qsort(String <Symbol> &data, String <int> &sorted_suffixes, int L, int R);
    bool cmp(int i, int j, String <Symbol> &data);
};


#endif //ARCHIVER_SUFFIXSORT_H
