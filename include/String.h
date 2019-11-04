#ifndef ARCHIVER_STRING_H
#define ARCHIVER_STRING_H

#include <vector>
#include <bitset>
#include "Symbol.h"

template <typename T>
class String {
private:
    std::vector <T> str;
public:
    explicit String(int size = 0);
    String <bool> toBool();
    String& add(T symb);
    String& operator+=(String &ot);
    String operator+(String &ot);
    String operator+(T symb);
    String& operator+=(T symb);
    T& operator[](int i);
    int size();
    void clear();
    void resize(int n);
};

template <>
class String<bool> {
private:
    std::vector <bool> str;
public:
    explicit String<bool>(int size = 0);
    String <Symbol> toSymb();
    void set(int i, bool bit);
    String<bool>& add(bool bit);
    String<bool>& operator+=(String<bool> &ot);
    String<bool> operator+(String<bool> &ot);
    String<bool> operator+(bool bit);
    String<bool>& operator+=(bool bit);
    const bool operator[](int i) const;
    int size();
    void clear();
    void resize(int n);
};

template class String<Symbol>;
template class String<bool>;

#endif //ARCHIVER_STRING_H
