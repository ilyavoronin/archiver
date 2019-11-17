#ifndef ARCHIVER_BWT_H
#define ARCHIVER_BWT_H

#include "AString.h"
#include "DataInfo.h"

class BWT {
    void encode(String <Symbol> &data, DataInfo &dataInfo); //overwriting data
    void decode(String <Symbol> &data, DataInfo &dataInfo); //overwriting data
};


#endif //ARCHIVER_BWT_H
