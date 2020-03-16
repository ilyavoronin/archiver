#ifndef ARCHIVER_DATAINFO_H
#define ARCHIVER_DATAINFO_H

#include "AString.h"
#include "mchar.h"
#include "Reader.h"
#include "Writer.h"

class DataInfo {
  public:
    DataInfo();
    void write(short int n);
    void write(int n);
    void write(mchar c);
    void write(String <mchar> &new_str);
    void write(String <bool> &new_str);
    void writeToFile(Writer &writer);
    void read(short int &n);
    void read(int &n);
    void read(String <mchar> &chars);
    void read(String <bool> &bin);
    mchar read();
    void readFromFile(Reader &reader);

    //When unzipping we run decoders in reversed order,
    //so when zipping we need to store information in the beginning of the DataInfo.
    //It is necessary to run this method before every data transformation
    //This method is automatically called when any read method is called
    void beginNewBlock();

  private:
    String <mchar> str_;

    //All data at first is writen to the buf_str_
    //When beginNewBlock is called, buf_str is copying in the beginning of str_
    String <mchar> buf_str_;
    int pos_;
};


#endif //ARCHIVER_DATAINFO_H
