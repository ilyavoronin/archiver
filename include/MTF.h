#ifndef ARCHIVER_MTF_H
#define ARCHIVER_MTF_H

#include <Astring.h>

class MTF {
public:
    void encode(String <Symbol> &data); //overwrites data
    void decode(String <Symbol> &data); //overwrites data
};


#endif //ARCHIVER_MTF_H
