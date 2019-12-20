#ifndef ARCHIVER_SUFFIXSORT_H
#define ARCHIVER_SUFFIXSORT_H

#include <functional>
#include "AString.h"


class SuffixSort {
  public:
    void sort(std::vector <int> &data, String <int> &sorted_suffixes);
    
  private:
    //SA-IS algorithm
    void sortSuffixes(std::vector <int> &data, std::vector <int> &sorted_suffixes);

    //sort suffixes if `lms_suffixes` has been sorted
    void inducedSort(std::vector <int> &data,
                     std::vector <bool> &type,
                     std::vector <int> &begin_S,
                     std::vector <int> &begin_L,
                     std::vector <int> &cnt_S,
                     std::vector <int> &lms_suffixes,
                     std::vector <int> &sorted_suffixes,
                     int max_symb_number);

    void calcuateTypes(std::vector <int> &data,
                       std::vector <bool> &type,
                       std::vector <int> &begin_S,
                       std::vector <int> &begin_L,
                       std::vector <int> &cnt_S,
                       std::vector <int> &cnt_L,
                       int max_symb_number,
                       const std::function <bool (int16_t, int16_t)> &cmp);
};


#endif //ARCHIVER_SUFFIXSORT_H
