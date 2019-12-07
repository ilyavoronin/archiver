#include "SuffixSort.h"

void SuffixSort::sort(String <Symbol> &data, String <int> &sorted_suffixes) {
    sorted_suffixes.resize(data.size());
    for (int i = 0; i < (int)data.size(); i++) {
        sorted_suffixes[i] = i;
    }
    qsort(data, sorted_suffixes, 0, data.size());
}

bool SuffixSort::cmp(int i, int j, String <Symbol> &data) {
    for (;(i < data.size() - 1) && (j < data.size() - 1); i++, j++) {
        if (data[i] < data[j]) {
            return true;
        }
        if (data[j] < data[i]) {
            return false;
        }
    }
    return i < j;
}

void SuffixSort::qsort(String<Symbol> &data, String<int> &sorted_suffixes, int L, int R) {
    if (R - L <= 1) {
        return;
    }
    int pivot = sorted_suffixes[L];
    String <int> le;
    String <int> ge;
    for (int i = L + 1; i < R; i++) {
        if (cmp(sorted_suffixes[i], pivot, data)) {
            le.add(sorted_suffixes[i]);
        }
        else {
            ge.add(sorted_suffixes[i]);
        }
    }
    int i = L;
    for (int j = 0; j < le.size(); j++) {
        sorted_suffixes[i++] = le[j];
    }
    sorted_suffixes[i++] = pivot;
    for (int j = 0; j < ge.size(); j++) {
        sorted_suffixes[i++] = ge[j];
    }
    qsort(data, sorted_suffixes, L, L + le.size());
    qsort(data, sorted_suffixes, L + le.size() + 1, R);
}