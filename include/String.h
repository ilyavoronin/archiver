#ifndef ARCHIVER_STRING_H
#define ARCHIVER_STRING_H

#include <vector>

template <typename T>
class String {
private:
    std::vector <T> str;
public:
    String(int size = 0);
    String& add(T symb);
    String& operator+=(String &ot);
    String operator+(String &ot);
    String operator+(T symb);
    String& operator+=(T symb);
    T& operator[](int i);
    int size();
};

#endif //ARCHIVER_STRING_H
