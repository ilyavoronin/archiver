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