#include <Archiver.h>
#include <AString.h>
#include <iostream>

std::string path = "C:\\Users\\voron\\Documents\\prog\\projects\\archiver\\files\\";

int main() {
    Archiver archiver;
    archiver.zip(path + "test.txt", path + "test_out.txt");
    archiver.unzip(path + "test_out.txt", path + "test_un.txt");
    return 0;
}