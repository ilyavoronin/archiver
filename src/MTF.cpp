#include "MTF.h"
#include <forward_list>
#include <iostream>

void MTF::encode(String <Symbol> &data) {
    std::forward_list <Symbol> alph;
    for (int i = 255; i >= 0; i--) {
        alph.push_front(i);
    }
    for (int i = 0; i < data.size(); i++) {
        auto iter = alph.begin(), prevIter = alph.before_begin();
        for (int j = 0; j < 256; j++) {
            if (*iter == data[i]) {
                alph.erase_after(prevIter);
                alph.push_front(data[i]);
                data[i] = j;
                break;
            }
            prevIter = iter++;
        }
    }
}

void MTF::decode(String <Symbol> &data) {
    std::forward_list <Symbol> alph;
    for (int i = 255; i >= 0; i--) {
        alph.push_front(i);
    }
    for (int i = 0; i < data.size(); i++) {
        auto iter = std::next(alph.before_begin(), data[i].get());
        auto nextIter = std::next(iter);
        data[i] = *nextIter;
        alph.erase_after(iter);
        alph.push_front(data[i]);
    }
}