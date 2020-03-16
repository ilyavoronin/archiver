#ifndef ARCHIVER_BWT_H
#define ARCHIVER_BWT_H

#include "mchar.h"
#include "IDataEncoder.h"
#include "AString.h"
#include "DataInfo.h"

class BWT : public IDataEncoder {
  public:
    void encode(String <mchar> &data, DataInfo &data_info) override; //overwrites data
    void decode(String <mchar> &data, DataInfo &data_info) override; //overwrites data
};


#endif //ARCHIVER_BWT_H
