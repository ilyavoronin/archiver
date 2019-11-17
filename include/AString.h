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
    String <bool> toBool() const;
    String& add(T symb);
    String& operator+=(const String &ot);
    String operator+(const String &ot) const;
    String operator+(T symb) const;
    String& operator+=(T symb);
    T& operator[](int i);
    const T& operator[](int i) const;
    bool operator==(const String &ot) const;
    int size() const;
    void clear();
    void resize(int n);
};

template <>
class String<bool> {
private:
    std::vector <bool> str;
public:
    explicit String<bool>(int size = 0);
    String <Symbol> toSymb() const;
    void set(int i, bool bit);
    String<bool>& add(bool bit);
    String<bool>& operator+=(const String<bool> &ot);
    String<bool> operator+(const String<bool> &ot) const;
    String<bool> operator+(bool bit) const;
    String<bool>& operator+=(bool bit);
    bool operator==(const String<bool> &ot) const;
    bool operator[](int i) const;
    int size() const;
    void clear();
    void resize(int n);
};

template class String<Symbol>;
template class String<bool>;
template class String<int>;

#endif //ARCHIVER_STRING_H
