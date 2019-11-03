#ifndef ARCHIVER_DATAINFO_H
#define ARCHIVER_DATAINFO_H

#include "String.h"
#include "Symbol.h"
#include "Reader.h"
#include "Writer.h"

class DataInfo {
private:
    String <Symbol> str;
    int pos;
public:
    DataInfo();
    void write(short int n);
    void write(int n);
    void write(Symbol c);
    void write(String <Symbol> &newStr);
    void write(String <bool> &newStr);
    void writeToFile(Writer &writer);
    void readFromFile(Reader &reader);
    void read(int &n);
    void read(short int &n);
    Symbol read();
};


#endif //ARCHIVER_DATAINFO_H
