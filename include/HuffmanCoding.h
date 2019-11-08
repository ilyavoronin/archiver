#ifndef ARCHIVER_HUFFMANCODING_H
#define ARCHIVER_HUFFMANCODING_H

#include "Symbol.h"
#include "AString.h"
#include "DataInfo.h"

#include <vector>
#include <map>

class HuffmanCoding {
private:
    const int ALPH_SIZE = 256;
public:
    void encode(String <Symbol> &data, DataInfo &dataInfo);   //overwriting data
    void decode(String <Symbol> &data, DataInfo &dataInfo);   //overwriting data
};


#endif //ARCHIVER_HUFFMANCODING_H
