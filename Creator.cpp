#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
using namespace std;
struct employee {
    int num;        // Идентификационный номер сотрудника
    char name[10];  // Имя сотрудника
    double hours;   // Количество отработанных часов
};

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: Creator <filename> <number of records>" << std::endl;
        return 1;
    }

    const char* filename = argv[1];
    std::cerr << filename << std::endl;
    int record_count = std::stoi(argv[2]);

    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile) {
        std::cerr << "Error opening file for writing!" << std::endl;
        return 1;
    }

    for (int i = 0; i < record_count; ++i) {
        employee emp;
        std::cout << "Enter employee number: ";
        std::cin >> emp.num;
        std::cout << "Enter employee name (up to 9 characters): ";
        std::cin >> emp.name;
        std::cout << "Enter hours worked: ";
        std::cin >> emp.hours;
        outFile.write(reinterpret_cast<char*>(&emp), sizeof(emp));
    }

    outFile.close();
    std::cout << "File created successfully." << std::endl;
    return 0;
}