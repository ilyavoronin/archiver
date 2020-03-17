#include "ConsoleUI.h"

#include <iostream>
#include <ctime>

#include "ECoders.h"
#include "Archiver.h"

void ConsoleUI::run(int argc, char **argv) {
    argv++;
    argc--;
    if (argc < 2) {
        std::cout << "Not enough arguments\n";
        return;
    }
    std::string file_path;
    std::vector <std::string> args = convertToStrings(argc, argv, file_path);
    if (file_path == "") {
        std::cout << "Enter the filename\n";
        return;
    }

    for (auto z : args) {
        if (z[0] == '-' && z[1] == 'b') {
            std::string ssize = "";
            if (z.size() <= 3) {
                std::cout << "-b_ must be followed by an integer";
                return;
            }
            for (int i = 3; i < z.size(); i++) {
                if (z[i] > '9' || z[i] < '0') {
                    std::cout << "-b must be followed by an integer";
                    return;
                }
                ssize += z[i];
            }
            block_size = std::stoi(ssize);
            if (z[2] == 'm') {
                block_size *= 1024;
            }
        }
    }

    Archiver arc;
    if (args[0] == "zip") {
        std::vector <Coders> algorithm;
        if (args[1] != "-c") {
            if (algorithms.count(args[1]) == 0) {
                std::cout << "Unknown argument '" << args[1] << "'\n";
                return;
            }
            algorithm = algorithms[args[1]];
        }
        else {
            std::cout << "Enter sequence:\n";
            std::cout << "0: Burrows-Wheeler transform(BWT)\n";
            std::cout << "1: Move-to-front transform(MTF)\n";
            std::cout << "2: Run Length Encoding(RLE)\n";
            std::cout << "3: Run Length Encoding 2\n";
            std::cout << "4: Huffman coding\n";
            std::cout << "5: Arithmetic coding\n";
            std::cout << "6: Incremental Frequency Count(IFC)\n";
            std::string seq;
            std::cin >> seq;
            for (auto num : seq) {
                algorithm.push_back(Coders(int(num - '0')));
            }
        }
        double t = clock();
        arc.zip(algorithm, block_size, file_path, file_path + ".arc");
        std::cerr << "zipped in " << (clock() - t) / CLOCKS_PER_SEC << " seconds\n";
        return;
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