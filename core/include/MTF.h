#ifndef ARCHIVER_MTF_H
#define ARCHIVER_MTF_H

#include "IDataEncoder.h"
#include "AString.h"

class MTF : public IDataEncoder {
  public:
    void encode(String <mchar> &data, DataInfo &data_info) override; //overwrites data
    void decode(String <mchar> &data, DataInfo &data_info) override; //overwrites data
};


#endif //ARCHIVER_MTF_H
