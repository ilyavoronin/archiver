#ifndef ARCHIVER_SYMBOL_H
#define ARCHIVER_SYMBOL_H

#include <cstdint>

class Symbol {
private:
    uint8_t ch;
public:
    Symbol(uint8_t ch_ = 0) {
        ch = ch_;
    }
    char toChar() const;
    int get() const;
    bool operator<(const Symbol &ot) const;
    bool operator==(const Symbol &ot) const;
    bool operator!=(const Symbol &ot) const;
};


#endif //ARCHIVER_SYMBOL_H
