#ifndef ARCHIVER_HUFFMANCODING_H
#define ARCHIVER_HUFFMANCODING_H

#include <vector>
#include <map>

#include "Symbol.h"
#include "AString.h"
#include "DataInfo.h"

class HuffmanCoding {
  public:
    void encode(String <Symbol> &data, DataInfo &data_info);   //overwrites data
    void decode(String <Symbol> &data, DataInfo &data_info);   //overwrites data

  private:
    const int kAlphabetSize = 256;
};


#endif //ARCHIVER_HUFFMANCODING_H
