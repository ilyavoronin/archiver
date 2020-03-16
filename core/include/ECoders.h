#ifndef ARCHIVER_CORE_INCLUDE_ECODERS_H_
#define ARCHIVER_CORE_INCLUDE_ECODERS_H_

#include "BWT.h"
#include "HuffmanCoding.h"
#include "MTF.h"

enum Coders {
    C_BWT     = 0,
    C_MTF     = 1,
    C_RLE     = 2,
    C_RLE2    = 3,
    C_HUFFMAN = 4
};

#endif //ARCHIVER_CORE_INCLUDE_ECODERS_H_
