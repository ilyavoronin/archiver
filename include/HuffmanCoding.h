#ifndef ARCHIVER_HUFFMANCODING_H
#define ARCHIVER_HUFFMANCODING_H

#include "Symbol.h"

#include <vector>

class HuffmanCoding {
public:
    void enocde(std::vector <Symbol> &data);
    void decode(std::vector <Symbol> &data);
};


#endif //ARCHIVER_HUFFMANCODING_H
