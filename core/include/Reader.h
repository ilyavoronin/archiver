#ifndef ARCHIVER_READER_H
#define ARCHIVER_READER_H

#include <fstream>
#include <vector>

#include "AString.h"

class Reader {
  public:
    enum Mode{STD = 0, BIN = 1};

    Reader(std::string input_file_name, int buf_size, Mode mode);

    ~Reader();

    bool read(String <mchar> &input, int input_size);
    void read(int &n);
    bool isEOF();
    void close();

  private:
    char *buf_;
    int buf_size_;
    int cnt_read_;
    std::ifstream in_;
};


#endif //ARCHIVER_READER_H
