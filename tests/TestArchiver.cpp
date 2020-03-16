#include "gtest/gtest.h"

#include <fstream>

#include "Archiver.h"

class ArchiverTests : public ::testing::Test {
  protected:
    static std::string input_filename;
    static std::string archived_filename;
    static std::string output_file_name;
    Archiver arc;
    static const int kTestSize = 5e5;
    static void SetUpTestSuite() {
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

std::string ArchiverTests::input_filename = "in.tmp";
std::string ArchiverTests::archived_filename = "arc.tmp";
std::string ArchiverTests::output_file_name = "out.tmp";


TEST_F(ArchiverTests, testZipUnzipFast) {
    arc.zip({C_BWT, C_MTF, C_RLE2, C_HUFFMAN}, 4096, input_filename, archived_filename);
    arc.unzip(archived_filename, output_file_name);

    ASSERT_TRUE(cmpFiles(input_filename, output_file_name));
}

TEST_F(ArchiverTests, testZipUnzipComb) {
    arc.zip({C_BWT, C_MTF, C_RLE2, C_RLE, C_MTF, C_BWT, C_RLE2, C_HUFFMAN, C_RLE}, 4096, input_filename, archived_filename);
    arc.unzip(archived_filename, output_file_name);

    ASSERT_TRUE(cmpFiles(input_filename, output_file_name));
}

TEST_F(ArchiverTests, testZipUnzipMultipleBlocks) {
    arc.zip({C_BWT, C_MTF, C_RLE2, C_MTF, C_RLE, C_BWT, C_RLE2, C_HUFFMAN, C_RLE}, 100, input_filename, archived_filename);
    arc.unzip(archived_filename, output_file_name);

    ASSERT_TRUE(cmpFiles(input_filename, output_file_name));
}

TEST_F(ArchiverTests, testZipUnzipMultipleSmallBlocks) {
    arc.zip({C_BWT, C_RLE, C_MTF, C_RLE2, C_RLE, C_MTF, C_BWT, C_RLE2, C_HUFFMAN, C_RLE}, 10, input_filename, archived_filename);
    arc.unzip(archived_filename, output_file_name);

    ASSERT_TRUE(cmpFiles(input_filename, output_file_name));
}