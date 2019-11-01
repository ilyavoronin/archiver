#ifndef ARCHIVER_DATAINFO_H
#define ARCHIVER_DATAINFO_H

#include <String.h>
#include <Symbol.h>

class DataInfo {
private:
    String <Symbol> str;
    int pos;
public:
    DataInfo();
    void write(short int n);
    void write(int n);
    void write(Symbol c);
};


#endif //ARCHIVER_DATAINFO_H
