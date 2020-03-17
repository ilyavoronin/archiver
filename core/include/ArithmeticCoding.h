#ifndef ARCHIVER_CORE_INCLUDE_ARITHMETICCODING_H_
#define ARCHIVER_CORE_INCLUDE_ARITHMETICCODING_H_

#include <vector>

#include "mchar.h"
#include "IDataEncoder.h"

class ArithmeticCoding : public IDataEncoder {
  public:
    void encode(String <mchar> &data, DataInfo &data_info) override;

    void decode(String <mchar> &data, DataInfo &data_info) override;

    void encodeBinary(String <bool> &data, DataInfo &data_info);

    void decodeBinary(String <bool> &data, DataInfo &data_info);

  private:
    const int kEpsSize = 18, kBinaryBlockSize = 30, tbound1 = 900;

    const unsigned long long MOD = (1ll << (kBinaryBlockSize - 1)),
                             N = (1ll << kBinaryBlockSize),
                             EPS = (1ll << kEpsSize);
};

#endif //ARCHIVER_CORE_INCLUDE_ARITHMETICCODING_H_
