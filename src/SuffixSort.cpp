#include "SuffixSort.h"

void SuffixSort::sort(String <Symbol> &data, String <int> &sortedSuffixes) {
    sortedSuffixes.resize(data.size());
    for (int i = 0; i < (int)data.size(); i++) {
        sortedSuffixes[i] = i;
    }
    qsort(data, sortedSuffixes, 0, data.size());
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

void SuffixSort::qsort(String<Symbol> &data, String<int> &sortedSuffixes, int L, int R) {
    if (R - L <= 1) {
        return;
    }
    int pivot = sortedSuffixes[L];
    String <int> le;
    String <int> ge;
    for (int i = L + 1; i < R; i++) {
        if (cmp(sortedSuffixes[i], pivot, data)) {
            le.add(sortedSuffixes[i]);
        }
        else {
            ge.add(sortedSuffixes[i]);
        }
    }
    int i = L;
    for (int j = 0; j < le.size(); j++) {
        sortedSuffixes[i++] = le[j];
    }
    sortedSuffixes[i++] = pivot;
    for (int j = 0; j < ge.size(); j++) {
        sortedSuffixes[i++] = ge[j];
    }
    qsort(data, sortedSuffixes, L, L + le.size());
    qsort(data, sortedSuffixes, L + le.size() + 1, R);
}