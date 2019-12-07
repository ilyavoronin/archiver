#ifndef ARCHIVER_DATAINFO_H
#define ARCHIVER_DATAINFO_H

#include "AString.h"
#include "Symbol.h"
#include "Reader.h"
#include "Writer.h"

class DataInfo {
  public:
    DataInfo();
    void write(short int n);
    void write(int n);
    void write(Symbol c);
    void write(String <Symbol> &new_str);
    void write(String <bool> &new_str);
    void writeToFile(Writer &writer);
    void read(short int &n);
    void read(int &n);
    void read(String <Symbol> &chars);
    void read(String <bool> &bin);
    Symbol read();
    void readFromFile(Reader &reader);
    void beginNewBlock();

  private:
    String <Symbol> str_;
    String <Symbol> buf_str_;
    int pos_;
};


#endif //ARCHIVER_DATAINFO_H
