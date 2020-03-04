#include "ConsoleUI.h"

#include <iostream>
#include <ctime>

#include "Archiver.h"

void ConsoleUI::run(std::string cmd, std::string file_path) {
    Archiver arc;
    if (cmd == "zip") {
        double t = clock();
        arc.zip(file_path, file_path + ".arc");
        std::cerr << "zipped in " << (clock() - t) / CLOCKS_PER_SEC << " seconds\n";
        return;
    }
    if (cmd == "unzip") {
        double t = clock();
        arc.unzip(file_path, file_path + ".unarc");
        std::cerr << "unzipped in " << (clock() - t) / CLOCKS_PER_SEC << " seconds\n";
        return;
    }
}