#ifndef ARCHIVER_READER_H
#define ARCHIVER_READER_H

#include <fstream>


class Reader {
private:
    char *buf;
    std::ifstream in;
public:
    Reader(std::string inputFileName, bool isBinary);
};


#endif //ARCHIVER_READER_H
