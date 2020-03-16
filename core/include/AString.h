#ifndef ARCHIVER_STRING_H
#define ARCHIVER_STRING_H

#include <vector>

#include "mchar.h"

template <typename T>
class String {
  public:
    explicit String(int size = 0);
    String(const std::vector <char> &v);

    String(const String<T> &ot) = default;
    String <T>& operator=(const String<T> &ot) = default;

    ~String() = default;

    String& add(T symb);
    String& operator+=(T symb);
    String& operator+=(const String &ot);
    String operator+(T symb) const;
    String operator+(const String &ot) const;
    T& operator[](int i);
    const T& operator[](int i) const;
    bool operator==(const String &ot) const;
    bool operator!=(const String &ot) const {return (*this) != ot;}

    int size() const;
    void clear();
    void resize(int n);
    void insertBegin(const String <T> &other);

    //This method implemented only for mchar
    //for other types returns empty String<bool>
    String <bool> toBool() const;

  private:
    std::vector <T> str_;
};

template <>
class String<bool> {
  public:
    explicit String<bool>(int size = 0);
    String(const std::vector <bool> &ot);

    String(const String <bool> &ot) = default;
    String <bool>& operator=(const String <bool> &ot) = default;

    ~String() = default;

    void add(bool bit);
    String<bool>& operator+=(bool bit);
    String<bool>& operator+=(const String<bool> &ot);
    String<bool> operator+(bool bit) const;
    String<bool> operator+(const String<bool> &ot) const;
    bool operator==(const String<bool> &ot) const;
    bool operator!=(const String<bool> &ot) const {return (*this) != ot;}
    bool operator[](int i) const;
    void set(int i, bool bit);

    int size() const;
    void clear();
    void resize(int n);
    String <mchar> toSymb() const;

  private:
    static const int isize = 8;
    static const int imod = 0x7;
    int cur_last_bit;
    int bit_size;
    std::vector <uint8_t> str_;
};

template class String<mchar>;
template class String<int>;

#endif //ARCHIVER_STRING_H
