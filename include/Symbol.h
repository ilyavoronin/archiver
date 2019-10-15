#ifndef ARCHIVER_SYMBOL_H
#define ARCHIVER_SYMBOL_H


class Symbol {
private:
    char ch;
public:
    Symbol(char ch_ = 0) {
        ch = ch_;
    }
    char toChar();
};


#endif //ARCHIVER_SYMBOL_H
