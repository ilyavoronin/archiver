#include <Archiver.h>
#include <AString.h>
#include <iostream>
#include <ctime>

std::string path = "C:\\Users\\voron\\Documents\\prog\\projects\\archiver\\files\\";

int main() {
    Archiver archiver;

    double t1 = clock();
    archiver.zip(path + "test.txt", path + "test_out.txt");
    std::cerr << "zipped in " << (clock() - t1) / CLOCKS_PER_SEC << " seconds\n";
    t1 = clock();
    archiver.unzip(path + "test_out.txt", path + "test_un.txt");
    std::cerr << "unzipped in " << (clock() - t1) / CLOCKS_PER_SEC << " seconds\n";
    return 0;
}