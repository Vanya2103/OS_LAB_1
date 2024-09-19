#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>

std::wstring stringToWString(const std::string& str) {

    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring wstrTo(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
    return wstrTo;
}

void printBinaryFile(const char* filename) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        std::cerr << "Error opening binary file!" << std::endl;
        return;
    }

    struct employee {
        int num;
        char name[10];
        double hours;
    };

    employee emp;
    while (inFile.read(reinterpret_cast<char*>(&emp), sizeof(emp))) {
        std::cout << "Employee Number: " << emp.num << ", Name: " << emp.name
            << ", Hours Worked: " << emp.hours << std::endl;
    }

    inFile.close();
}

void printReportFile(const char* filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Error opening report file!" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        std::cout << line << std::endl;
    }

    inFile.close();
}

int main() {


    setlocale(LC_ALL, "rus");     // Установка локали для вывода на русском языке

    std::string binaryFile, reportFile;
    int recordCount;
    double hourlyRate;

    // 1. Запрос имени бинарного файла и количества записей
    std::cout << "Enter the name of the binary file: ";
    std::cin >> binaryFile;
    std::cout << "Enter the number of records: ";
    std::cin >> recordCount;

    binaryFile = binaryFile + ".bin";

    // 2. Запуск утилиты Creator
    STARTUPINFO si = { sizeof(STARTUPINFO) };
    PROCESS_INFORMATION pi;

    std::string creatorCmd = "Creator " + binaryFile + " " + std::to_string(recordCount);

    std::wstring wCreatorCmd = stringToWString(creatorCmd);

    if (!CreateProcess(NULL, const_cast<wchar_t*>(wCreatorCmd.c_str()), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) // как , о запущ 
    {
        std::cerr << "Failed to launch Creator process!" << std::endl;
        return 1;
    }


    // 3. Ожидание завершения Creator
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess); //дескриптор нового процесса
    CloseHandle(pi.hThread); //дескриптор основного потока нового процесса.

    // 4. Вывод содержимого бинарного файла на консоль
    std::cout << "Contents of the binary file:" << std::endl;
    printBinaryFile(binaryFile.c_str());

    // 5. Запрос имени файла отчета и оплаты за час
    std::cout << "Enter the name of the report file: ";
    std::cin >> reportFile;
    std::cout << "Enter the hourly rate: ";
    std::cin >> hourlyRate;

    reportFile = reportFile + ".txt";
    // 6. Запуск утилиты Reporter
    std::string reporterCmd = "Reporter " + binaryFile + " " + reportFile + " " + std::to_string(hourlyRate);
    std::wstring wreporterCmd = stringToWString(reporterCmd);

    if (!CreateProcess(NULL, const_cast<wchar_t*>(wreporterCmd.c_str()), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        std::cerr << "Failed to launch Reporter process!" << std::endl;
        return 1;
    }

    // 7. Ожидание завершения Reporter
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    // 8. Вывод отчета на консоль
    std::cout << "Report contents:" << std::endl;
    printReportFile(reportFile.c_str());

    // 9. Завершение работы
    return 0;
}