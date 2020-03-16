#ifndef ARCHIVER_HUFFMANCODING_H
#define ARCHIVER_HUFFMANCODING_H

#include <vector>
#include <map>

#include "IDataEncoder.h"
#include "AString.h"
#include "DataInfo.h"

class HuffmanCoding : public IDataEncoder {
  public:
    void encode(String <mchar> &data, DataInfo &data_info) override;   //overwrites data
    void decode(String <mchar> &data, DataInfo &data_info) override ;   //overwrites data

  private:
    const int kAlphabetSize = 256;
};


#endif //ARCHIVER_HUFFMANCODING_H
