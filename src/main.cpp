#include <Archiver.h>
#include <String.h>

#include <iostream>

std::string path = "C:\\Users\\voron\\Documents\\prog\\projects\\archiver\\files\\";

int main() {
    Archiver archiver;
    archiver.zip(path + "test.txt", path + "test_out.txt");
    return 0;
}