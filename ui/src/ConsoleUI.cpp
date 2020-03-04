#include "ConsoleUI.h"

#include <iostream>
#include <ctime>

#include "ECoders.h"
#include "Archiver.h"
#include "BWT.h"
#include "HuffmanCoding.h"
#include "MTF.h"

void ConsoleUI::run(int argc, char **argv) {
    argv++;
    argc--;
    if (argc < 2) {
        std::cout << "Not enough arguments\n";
        return;
    }
    if (argc >= 4) {
        std::cout << "Too many arguments";
        return;
    }
    std::string file_path;
    std::vector <std::string> args = convertToStrings(argc, argv, file_path);
    if (file_path == "") {
        std::cout << "Enter the filename\n";
        return;
    }
    Archiver arc;
    if (args[0] == "zip") {
        if (args[1] != "-c") {
            if (algorithms.count(args[1]) == 0) {
                std::cout << "Unknown argument '" << args[1] << "'\n";
                return;
            }
            auto algorithm = algorithms[args[1]];
            double t = clock();
            arc.zip(algorithm, file_path, file_path + ".arc");
            std::cerr << "zipped in " << (clock() - t)/CLOCKS_PER_SEC << " seconds\n";
            return;
        }
        else {
            
        }
    }
    if (args[0] == "unzip") {
        double t = clock();
        arc.unzip(file_path, file_path + ".unarc");
        std::cerr << "unzipped in " << (clock() - t) / CLOCKS_PER_SEC << " seconds\n";
        return;
    }
    std::cout << "Unknown argument '" << args[0] << "'\n";
}

std::vector <std::string> ConsoleUI::convertToStrings(int argc, char **argv, std::string &filename) {
    std::vector <std::string> res;
    for (int i = 0; i < argc; i++) {
        if (i > 0 && argv[i][0] != '-') {
            filename = argv[i];
        }
        else {
            res.push_back(argv[i]);
        }
    }
    return res;
}