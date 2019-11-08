#ifndef ARCHIVER_READER_H
#define ARCHIVER_READER_H

#include <fstream>
#include <vector>
#include "Symbol.h"
#include "AString.h"

class Reader {
private:
    char *buf;
    int bufSize;
    int cntRead;
    std::ifstream in;
public:
    enum Mode{STD = 0, BIN = 1};
    Reader(std::string inputFileName, int bufSize_, Mode mode);
    ~Reader();
    bool read(String <Symbol> &input, int inputSize);
    bool isEOF();
    void read(int &n);
    void close();
};


#endif //ARCHIVER_READER_H
