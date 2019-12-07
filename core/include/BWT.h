#ifndef ARCHIVER_BWT_H
#define ARCHIVER_BWT_H

#include "AString.h"

#include "DataInfo.h"

class BWT {
  public:
    void encode(String <Symbol> &data, DataInfo &data_info); //overwrites data
    void decode(String <Symbol> &data, DataInfo &data_info); //overwrites data
};


#endif //ARCHIVER_BWT_H
