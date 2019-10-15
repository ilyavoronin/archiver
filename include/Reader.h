#ifndef ARCHIVER_READER_H
#define ARCHIVER_READER_H

#include <fstream>
#include <vector>
#include <Symbol.h>

class Reader {
private:
    char *buf;
    int bufSize;
    int sucRead;
    bool eof;
    std::ifstream in;
public:
    enum Mode{STD = 0, BIN = 1};
    Reader(std::string inputFileName, int bufSize_, Mode mode);
    ~Reader();
    bool read(std::vector <Symbol> &input);
    bool isEOF();
};


#endif //ARCHIVER_READER_H
