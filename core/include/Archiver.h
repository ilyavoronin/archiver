#ifndef ARCHIVER_ARCHIVER_H
#define ARCHIVER_ARCHIVER_H

#include "Symbol.h"

#include <vector>
#include <string>

#include "DataInfo.h"
#include "AString.h"
#include "ECoders.h"
#include "IDataEncoder.h"

class Archiver {
  public:
    Archiver();
    ~Archiver();
    void zip(std::vector <Coders> algorithm, int block_size_k, std::string input_file_name, std::string output_file_name);
    void unzip(std::string input_file_name, std::string output_file_name);
  private:
    int block_size;
    std::map <Coders, IDataEncoder *> coders;

    void zipBlock(String <Symbol> &block, DataInfo &data_info, std::vector <IDataEncoder *> coding_sequence);
    void unzipBlock(String <Symbol> &block, DataInfo &data_info, std::vector <IDataEncoder *> coding_sequence);
    std::vector <IDataEncoder *> toCoderSequence(std::vector <Coders> algorithm);
};

#endif //ARCHIVER_ARCHIVER_H
