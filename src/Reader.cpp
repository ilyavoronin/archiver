#include "Reader.h"

Reader::Reader(std::string inputFileName, bool isBinary) {
    if (isBinary) {
        in.open(inputFileName, std::ios::binary);
    }
    else {
        in.open(inputFileName);
    }
}