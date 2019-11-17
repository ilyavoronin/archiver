#include "BWT.h"
#include "SuffixSort.h"

void BWT::encode(String<Symbol> &data, DataInfo &dataInfo) {
    String <int> sortedSuffixes;
    String <Symbol> newData(data.size());
    SuffixSort().sort(data, sortedSuffixes);
    int n = data.size();
    int firstSuffixNumber;
    for (int i = 0; i < n; i++) {
        newData[i] = data[(sortedSuffixes[i] + n - 1) % n];
        if (sortedSuffixes[i] == 0) {
            firstSuffixNumber = i;
        }
    }
    std::swap(data, newData);
    dataInfo.write(firstSuffixNumber);
}

void BWT::decode(String<Symbol> &data, DataInfo &dataInfo) {
    
}