#ifndef ARCHIVER_CORE_INCLUDE_IFC_H_
#define ARCHIVER_CORE_INCLUDE_IFC_H_

#include "IDataEncoder.h"

class IFC : public IDataEncoder {
  public:
    void encode(String<mchar> &data, DataInfo &data_info) override;
    void decode(String<mchar> &data, DataInfo &data_info) override;
  private:
    const int windowSize = 8, const1 = 64;
    const int const3 = 256, const4 = 16;
};

#endif //ARCHIVER_CORE_INCLUDE_IFC_H_
