#ifndef ARCHIVER_ARCHIVER_H
#define ARCHIVER_ARCHIVER_H

#include <string>

class Archiver {
private:
    const int BLOCK_SIZE = (1 << 22);
public:
    void zip(std::string inputFileName, std::string outputFileName);
    void unzip(std::string inputFileName, std::string outputFileName);
};

#endif //ARCHIVER_ARCHIVER_H
