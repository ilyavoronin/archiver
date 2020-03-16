#ifndef ARCHIVER_WRITER_H
#define ARCHIVER_WRITER_H

#include <fstream>
#include <vector>

#include "AString.h"


class Writer {
  public:
    enum Mode{STD = 0, BIN = 1, APP = 2, BINAPP = 3};

    Writer(std::string outputFileName, int bufSize_, Mode mode);

    ~Writer();

    void write(String <mchar> &output);
    void write(int n);
    void close();

  private:
    char* buf_;
    int buf_size_;
    std::ofstream out_;
};


#endif //ARCHIVER_WRITER_H
