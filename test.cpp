#include "pch.h"
#include "gtest/gtest.h"
#include <fstream>

// Пример функции, которую мы тестируем
bool fileExists(const std::string& fileName) {
    std::ifstream infile(fileName);
    return infile.good();
}

// Юнит тест для проверки существования файла
TEST(FileTest, FileExists) {
    std::string testFileName = "output.bin";

    // Создаем тестовый файл перед проверкой
    std::ofstream outfile(testFileName);
    outfile << "Test data"; // Можно записать какие-то данные
    outfile.close();

    // Проверка существования файла
    ASSERT_TRUE(fileExists(testFileName)) << "File " << testFileName << " should exist.";

    // Удаляем файл после теста (опционально)
    std::remove(testFileName.c_str());
}

TEST(FileTest, EmptyFileExists) {
    std::string testFileName = "empty_file.bin";

    // Создаем пустой файл
    std::ofstream outfile(testFileName);
    outfile.close();

    // Проверка, что пустой файл существует
    ASSERT_TRUE(fileExists(testFileName)) << "File " << testFileName << " should exist.";

    std::remove(testFileName.c_str());
}

TEST(FileTest, EmptyFileName) {
    std::string testFileName = "";

    // Проверка, что для пустого имени файла функция возвращает false
    ASSERT_FALSE(fileExists(testFileName)) << "Empty file name should return false.";
}
