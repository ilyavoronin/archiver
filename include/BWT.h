#ifndef ARCHIVER_BWT_H
#define ARCHIVER_BWT_H

#include "AString.h"

#include "DataInfo.h"

class BWT {
  public:
    void encode(String <Symbol> &data, DataInfo &data_info); //overwriting data
    void decode(String <Symbol> &data, DataInfo &data_info); //overwriting data
};


#endif //ARCHIVER_BWT_H
