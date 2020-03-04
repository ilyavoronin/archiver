#ifndef ARCHIVER_CORE_SRC_IDATAENCODER_H_
#define ARCHIVER_CORE_SRC_IDATAENCODER_H_

#include <DataInfo.h>

class IDataEncoder {
  public:
    virtual ~IDataEncoder() {}
    virtual void encode(String <Symbol> &data, DataInfo &data_info) = 0;
    virtual void decode(String <Symbol> &data, DataInfo &data_info) = 0;
};

#endif //ARCHIVER_CORE_SRC_IDATAENCODER_H_
