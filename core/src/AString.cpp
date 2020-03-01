#include "AString.h"

template <typename T>
String<T>::String(int size) {
    str_.resize(size);
}

template <typename T>
String<T>& String<T>::add(T symb) {
    str_.push_back(symb);
    return *this;
}

template <typename T>
String<T>& String<T>::operator+=(T symb) {
    add(symb);
    return *this;
}

template <typename T>
String<T>& String<T>::operator+=(const String &ot) {
    this->str_.insert(this->str_.end(), ot.str_.begin(), ot.str_.end());
    return *this;
}

template <typename T>
String<T> String<T>::operator+(T symb) const {
    String<T> tmp = *this;
    tmp.add(symb);
    return tmp;
}

template <typename T>
String<T> String<T>::operator+(const String &ot) const {
    String<T> tmp = *this;
    tmp += ot;
    return tmp;
}

template <typename T>
T& String<T>::operator[](int i) {
    return str_[i];
}

template <typename T>
const T& String<T>::operator[](int i) const {
    return str_[i];
}

template <typename T>
bool String<T>::operator==(const String &ot) const {
    if (ot.size() != this->size()) {
        return false;
    }
    for (int i = 0; i < ot.size(); i++) {
        if (ot[i] != this->str_[i]) {
            return false;
        }
    }
    return true;
}

template <typename T>
int String<T>::size() const {
    return str_.size();
}

template <typename T>
void String<T>::clear() {
    str_.clear();
}

template <typename T>
void String<T>::resize(int n) {
    str_.resize(n);
}

template <typename T>
void String<T>::insertBegin(const String<T> &other) {
    str_.insert(this->str_.begin(), other.str_.begin(), other.str_.end());
}

template <typename T>
String<bool> String<T>::toBool() const {
    String <bool> res(0);
    return res;
}

template <>
String<bool> String<Symbol>::toBool() const {
    String <bool> res(str_.size() * 8);
    for (int i = 0; i < str_.size(); i++) {
        for (int j = 0; j < 8; j++) {
            if (((str_[i].get_char()) & (1 << j)) != 0) {
                res.set(i * 8 + j, 1);
            }
            else {
                res.set(i * 8 + j, 0);
            }
        }
    }
    return res;
}




String<bool>::String(int size) {
    str_.resize((size - 1) / isize + 1);
    cur_last_bit = (size - 1) % isize + 1;
    bit_size = size;
}

String<bool>& String<bool>::add(bool bit) {
    if (cur_last_bit == isize) {
        str_.push_back(bit);
    }
    else {
        str_[str_.size() - 1] |= (1 << cur_last_bit++);
    }
    bit_size++;
    return *this;
}

String<bool>& String<bool>::operator+=(bool bit) {
    add(bit);
    bit_size++;
    return *this;
}

String<bool>& String<bool>::operator+=(const String <bool> &ot) {
    for (int i = 0; i < ot.size(); i++) {
        add(ot[i]);
    }
    return *this;
}

String<bool> String<bool>::operator+(bool symb) const {
    String<bool> tmp = *this;
    tmp.add(symb);
    return tmp;
}

String<bool> String<bool>::operator+(const String <bool> &ot) const {
    String<bool> tmp = *this;
    for (int i = 0; i < ot.size(); i++) {
        tmp.add(ot[i]);
    }
    return tmp;
}

bool String<bool>::operator==(const String<bool> &ot) const {
    if (ot.bit_size != this->bit_size) {
        return false;
    }
    for (int i = 0; i < ot.size(); i++) {
        if (ot[i] != this->str_[i]) {
            return false;
        }
    }
    return true;
}

bool String<bool>::operator[](int i) const {
    return (str_[i / isize] & (1 << (i % isize))) != 0;
}

void String<bool>::set(int i, bool bit) {
    str_[i / isize] |= (1 << (i % isize));
}

int String<bool>::size() const {
    return bit_size;
}

void String<bool>::clear() {
    str_.clear();
    cur_last_bit = 8;
    bit_size = 0;
}

void String<bool>::resize(int n) {
    str_.resize((n - 1) / isize + 1);
    bit_size = n;
    cur_last_bit = (bit_size - 1) % isize + 1;
    //the number of extra bits
    int k = (isize - n % isize) % isize;
    if (n != 0) {
        str_[str_.size() - 1] &= (((1 << isize) - 1) << k);
    }
}

String<Symbol> String<bool>::toSymb() const {
    String<Symbol> res(str_.size());
    for (int i = 0; i < str_.size(); i++) {
        res[i] = str_[i];
    }
    return res;
}