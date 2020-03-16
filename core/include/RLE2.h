#ifndef ARCHIVER_CORE_SRC_RLE2_H_
#define ARCHIVER_CORE_SRC_RLE2_H_

#include "IDataEncoder.h"

class RLE2 : public IDataEncoder {
  public:
    void encode(String <mchar> &data, DataInfo &data_info) override;
    void decode(String <mchar> &data, DataInfo &data_info) override;
};

#endif //ARCHIVER_CORE_SRC_RLE2_H_
