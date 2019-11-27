#ifndef ARCHIVER_ARCHIVER_H
#define ARCHIVER_ARCHIVER_H

#include "Symbol.h"
#include "DataInfo.h"
#include "AString.h"

#include <vector>
#include <string>

class Archiver {
private:
    const int BLOCK_SIZE = (1 << 9);
    void zip_block(String <Symbol> &block, DataInfo &dataInfo);
    void unzip_block(String <Symbol> &block, DataInfo &dataInfo);
public:
    void zip(std::string inputFileName, std::string outputFileName);
    void unzip(std::string inputFileName, std::string outputFileName);
};

#endif //ARCHIVER_ARCHIVER_H
