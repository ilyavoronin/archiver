#include "String.h"

template <typename T>
String<T>::String(int size) {
    str.resize(size);
}

template <typename T>
String<T>& String<T>::add(T symb) {
    str.push_back(symb);
    return *this;
}

template <typename T>
String<T>& String<T>::operator+=(String &ot) {
    this->str.insert(this->str.begin(), ot.str.begin(), ot.str.end());
    return *this;
}

template <typename T>
String<T> String<T>::operator+(String &ot) {
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
String<T> String<T>::operator+(T symb) {
    String<T> tmp = *this;
    tmp.add(symb);
    return tmp;
}

template <typename T>
T& String<T>::operator[](int i) {
    return str[i];
}

template <typename T>
int String<T>::size() {
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

String<bool>& String<bool>::add(bool bit) {
    str.push_back(bit);
    return *this;
}

String<bool>& String<bool>::operator+=(String<bool> &ot) {
    this->str.insert(this->str.begin(), ot.str.begin(), ot.str.end());
    return *this;
}

String<bool> String<bool>::operator+(String<bool> &ot) {
    String<bool> tmp = *this;
    tmp += ot;
    return tmp;
}

String<bool>& String<bool>::operator+=(bool bit) {
    add(bit);
    return *this;
}

String<bool> String<bool>::operator+(bool symb) {
    String<bool> tmp = *this;
    tmp.add(symb);
    return tmp;
}

const bool String<bool>::operator[](int i) const {
    return str[i];
}

int String<bool>::size() {
    return str.size();
}

void String<bool>::clear() {
    str.clear();
}

void String<bool>::resize(int n) {
    str.resize(n);
}