#ifndef ARCHIVER_BWT_H
#define ARCHIVER_BWT_H

#include "IDataEncoder.h"
#include "AString.h"
#include "DataInfo.h"

class BWT : public IDataEncoder {
  public:
    void encode(String <Symbol> &data, DataInfo &data_info) override; //overwrites data
    void decode(String <Symbol> &data, DataInfo &data_info) override; //overwrites data
};


#endif //ARCHIVER_BWT_H
