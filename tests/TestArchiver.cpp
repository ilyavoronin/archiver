#include "gtest/gtest.h"

#include <Archiver.h>
#include <fstream>

class ArchiverTests : public ::testing::Test {
protected:
    std::string inFilename = "in.tmp";
    std::string arcFileName = "arc.tmp";
    std::string outFileName = "out.tmp";
    Archiver arc;
    const int TEST_SIZE = 5e6;
    void SetUp() override {
        std::ofstream out(inFilename, std::ios::binary);
        for (int i = 0; i < TEST_SIZE; i++) {
            out << char(rand() % 256);
        }
        out.close();
    };

    bool cmpFiles(std::string file1, std::string file2) {
        std::ifstream in1(file1, std::ios::binary);
        std::ifstream in2(file2, std::ios::binary);
        while (!in1.eof()) {
            char c1 = in1.get();
            char c2 = in2.get();
            if (c1 != c2) {
                return false;
            }
        }
        return true;
    }
};

TEST_F(ArchiverTests, testZipUnzip) {
    arc.zip(inFilename, arcFileName);
    arc.unzip(arcFileName, outFileName);
    ASSERT_TRUE(cmpFiles(inFilename, outFileName));
}