#include "BWT.h"
#include "SuffixSort.h"

void BWT::encode(String<Symbol> &data, DataInfo &dataInfo) {
    String <int> sortedSuffixes;
    data.add(Symbol(255)); //In sort and in decoding we consider that new Symbol is > than others
    String <Symbol> newData(data.size());
    int nnn = data.size();
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
    int n = data.size();
    int firstSuffixNumber;
    dataInfo.read(firstSuffixNumber);
    std::vector <int> cntLess(257, 0);
    String <int> cntEqPrev(data.size());
    String <Symbol> resData((int)data.size() - 1);
    for (int i = 0; i < n; i++) {
        if (i == firstSuffixNumber) {
            cntEqPrev[i] = 0;
            continue;
        }
        cntEqPrev[i] = cntLess[data[i].get()];
        cntLess[data[i].get()]++;
    }
    int cntPrev = cntLess[0];
    cntLess[0] = 0;
    for (int i = 1; i < 256; i++) {
        int tmp = cntLess[i];
        cntLess[i] = cntLess[i - 1] + cntPrev;
        cntPrev = tmp;
    }
    cntLess[256] = n - 1;
    int curIndex = firstSuffixNumber;
    int prevSymbol = 256;
    for (int i = 1; i < n; i++) {
        int newIndex = cntEqPrev[curIndex] + cntLess[prevSymbol];
        resData[n - i - 1] = data[newIndex];
        prevSymbol = resData[n - i - 1].get();
        curIndex = newIndex;
    }
    std::swap(data, resData);
}