#include "AString.h"

template <typename T>
String<T>::String(int size) {
    str.resize(size);
}

template <typename T>
String<bool> String<T>::toBool() const {
    String <bool> res(str.size() * 8);
    for (int i = 0; i < str.size(); i++) {
        for (int j = 0; j < 8; j++) {
            if (((str[i].toChar()) & (1 << j)) != 0) {
                res.set(i * 8 + j, 1);
            }
            else {
                res.set(i * 8 + j, 0);
            }
        }
    }
    return res;
}

template <typename T>
String<T>& String<T>::add(T symb) {
    str.push_back(symb);
    return *this;
}

template <typename T>
String<T>& String<T>::operator+=(const String &ot) {
    this->str.insert(this->str.end(), ot.str.begin(), ot.str.end());
    return *this;
}

template <typename T>
String<T> String<T>::operator+(const String &ot) const {
    String<T> tmp = *this;
    tmp += ot;
    return tmp;
}

template <typename T>
String<T>& String<T>::operator+=(T symb) {
    add(symb);
    return *this;
}

template <typename T>
String<T> String<T>::operator+(T symb) const {
    String<T> tmp = *this;
    tmp.add(symb);
    return tmp;
}

template <typename T>
T& String<T>::operator[](int i) {
    return str[i];
}

template <typename T>
const T& String<T>::operator[](int i) const {
    return str[i];
}

template <typename T>
int String<T>::size() const {
    return str.size();
}

template <typename T>
void String<T>::clear() {
    str.clear();
}

template <typename T>
void String<T>::resize(int n) {
    str.resize(n);
}





String<bool>::String(int size) {
    str.resize(size);
}

void String<bool>::set(int i, bool bit) {
    str[i] = bit;
}

String<Symbol> String<bool>::toSymb() const {
    String<Symbol> res(((int)str.size() - 1) / 8 + 1);
    for (int i = 0; i < (int)this->size(); i += 8) {
        uint8_t c = 0;
        for (int j = 0; j < 8; j++) {
            if (i + j < str.size() && str[i + j] == 1) {
                c |= (1 << j);
            }
        }
        res[i / 8] = c;
    }
    return res;
}

String<bool>& String<bool>::add(bool bit) {
    str.push_back(bit);
    return *this;
}

String<bool>& String<bool>::operator+=(const String<bool> &ot) {
    this->str.insert(this->str.end(), ot.str.begin(), ot.str.end());
    return *this;
}

String<bool> String<bool>::operator+(const String<bool> &ot) const {
    String<bool> tmp = *this;
    tmp += ot;
    return tmp;
}

String<bool>& String<bool>::operator+=(bool bit) {
    add(bit);
    return *this;
}

String<bool> String<bool>::operator+(bool symb) const {
    String<bool> tmp = *this;
    tmp.add(symb);
    return tmp;
}

bool String<bool>::operator[](int i) const {
    return str[i];
}

int String<bool>::size() const {
    return str.size();
}

void String<bool>::clear() {
    str.clear();
}

void String<bool>::resize(int n) {
    str.resize(n);
}