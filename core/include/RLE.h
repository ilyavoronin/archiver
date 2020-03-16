#ifndef ARCHIVER_CORE_INCLUDE_RLE_H_
#define ARCHIVER_CORE_INCLUDE_RLE_H_

#include "IDataEncoder.h"


//two or more symbols are replaced with two symbols and the length of the run
class RLE : public IDataEncoder {
  public:
    void encode(String <mchar> &data, DataInfo &data_info) override;
    void decode(String <mchar> &data, DataInfo &data_info) override;
  private:
    void write_int(int n, String <mchar> &res);
    //reads int that begins from position i in data
    int read_int(int &i, String <mchar> &data);
};

#endif //ARCHIVER_CORE_INCLUDE_RLE_H_
