#ifndef ARCHIVER_ARCHIVER_H
#define ARCHIVER_ARCHIVER_H

#include "Symbol.h"
#include "DataInfo.h"

#include <vector>
#include <string>

class Archiver {
private:
    const int BLOCK_SIZE = (1 << 22);
    void zip_block(String <Symbol> &block, DataInfo &dataInfo);
public:
    void zip(std::string inputFileName, std::string outputFileName);
    void unzip(std::string inputFileName, std::string outputFileName);
};

#endif //ARCHIVER_ARCHIVER_H
