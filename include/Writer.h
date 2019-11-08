#ifndef ARCHIVER_WRITER_H
#define ARCHIVER_WRITER_H


#include <fstream>
#include <vector>
#include <Symbol.h>
#include "AString.h"


class Writer {
private:
    char* buf;
    int bufSize;
    std::ofstream out;
public:
    enum Mode{STD = 0, BIN = 1, APP = 2, BINAPP = 3};
    Writer(std::string outputFileName, int bufSize_, Mode mode);
    ~Writer();
    void write(String <Symbol> &output);
    void write(int n);
    void close();
};


#endif //ARCHIVER_WRITER_H
