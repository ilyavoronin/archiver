#ifndef ARCHIVER_ARCHIVER_H
#define ARCHIVER_ARCHIVER_H

#include "Symbol.h"

#include <vector>
#include <string>

#include "DataInfo.h"
#include "AString.h"

class Archiver {
  public:
    void zip(std::string input_file_name, std::string output_file_name);
    void unzip(std::string input_file_name, std::string output_file_name);
  private:
    const int kBlockSize = (1 << 9);

    void zipBlock(String <Symbol> &block, DataInfo &data_info);
    void unzipBlock(String <Symbol> &block, DataInfo &data_info);
};

#endif //ARCHIVER_ARCHIVER_H
