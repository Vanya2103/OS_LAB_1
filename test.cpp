#include "pch.h"
#include "gtest/gtest.h"
#include <fstream>

// ������ �������, ������� �� ���������
bool fileExists(const std::string& fileName) {
    std::ifstream infile(fileName);
    return infile.good();
}

// ���� ���� ��� �������� ������������� �����
TEST(FileTest, FileExists) {
    std::string testFileName = "output.bin";

    // ������� �������� ���� ����� ���������
    std::ofstream outfile(testFileName);
    outfile << "Test data"; // ����� �������� �����-�� ������
    outfile.close();

    // �������� ������������� �����
    ASSERT_TRUE(fileExists(testFileName)) << "File " << testFileName << " should exist.";

    // ������� ���� ����� ����� (�����������)
    std::remove(testFileName.c_str());
}

TEST(FileTest, EmptyFileExists) {
    std::string testFileName = "empty_file.bin";

    // ������� ������ ����
    std::ofstream outfile(testFileName);
    outfile.close();

    // ��������, ��� ������ ���� ����������
    ASSERT_TRUE(fileExists(testFileName)) << "File " << testFileName << " should exist.";

    std::remove(testFileName.c_str());
}

TEST(FileTest, EmptyFileName) {
    std::string testFileName = "";

    // ��������, ��� ��� ������� ����� ����� ������� ���������� false
    ASSERT_FALSE(fileExists(testFileName)) << "Empty file name should return false.";
}
