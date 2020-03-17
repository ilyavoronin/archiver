#ifndef ARCHIVER_UI_CONSOLEUI_H_
#define ARCHIVER_UI_CONSOLEUI_H_

#include <string>
#include <map>
#include <vector>

#include "IDataEncoder.h"
#include "ECoders.h"

class ConsoleUI {
  public:
    void run(int argc, char **argv);

  private:
    std::vector <std::string> convertToStrings(int argc, char **argv, std::string &filename);

    std::map <std::string, std::vector <Coders> > algorithms {
        {"-fast", {C_BWT, C_RLE, C_IFC, C_HUFFMAN}},
        {"-comp", {C_BWT, C_RLE, C_IFC, C_ACODING}}
    };
    //default settings
    int block_size = 4096; // in kilobytes;
};

#endif //ARCHIVER_UI_CONSOLEUI_H_
