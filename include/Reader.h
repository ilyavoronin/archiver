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
    Reader(std::string inputFileName, bool isBinary, int bufSize_);
    bool read(std::vector <Symbol> &input);
    bool isEOF();
};


#endif //ARCHIVER_READER_H
