#include "gtest/gtest.h"

#include <Archiver.h>
#include <fstream>

class ArchiverTests : public ::testing::Test {
  protected:
    std::string input_filename = "in.tmp";
    std::string archived_filename = "arc.tmp";
    std::string output_file_name = "out.tmp";
    Archiver arc;
    const int kTestSize = 5e5;
    void SetUp() override {
        std::ofstream out(input_filename, std::ios::binary);
        srand(17);
        for (int i = 0; i < kTestSize; i++) {
            out << static_cast<char>(rand() % 256);
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
    arc.zip(input_filename, archived_filename);
    arc.unzip(archived_filename, output_file_name);

    ASSERT_TRUE(cmpFiles(input_filename, output_file_name));
}