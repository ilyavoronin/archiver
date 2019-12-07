#ifndef ARCHIVER_SYMBOL_H
#define ARCHIVER_SYMBOL_H

#include <cstdint>

class Symbol {
  public:
    Symbol(uint8_t ch_ = 0) {
        ch = ch_;
    }
    char get_char() const;
    int get() const;

    bool operator<(const Symbol &ot) const;
    bool operator>(const Symbol &ot) const;
    bool operator<=(const Symbol &ot) const;
    bool operator>=(const Symbol &ot) const;
    bool operator==(const Symbol &ot) const;
    bool operator!=(const Symbol &ot) const;

  private:
    uint8_t ch;
};


#endif //ARCHIVER_SYMBOL_H
