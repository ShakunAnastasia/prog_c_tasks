/*
BitFields Project C++ - Test File & Benchmark
Student: Shakun Anastasia
Group: compmath, 2 course
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <chrono> // Бібліотека для заміру часу
#include "../src/BitFields.hpp"

using namespace std;
using namespace std::chrono;

void logResult(const string& msg) {
    ofstream f("TestResult_CPP.txt", ios::app);
    if(f.is_open()) {
        f << msg << endl;
        f.close();
    }
}

// Порівняння швидкості.
void runBenchmark() {
    cout << "\n-- Performance Benchmark (1 000 000 iter) --\n";
    cout << "Comparing creation and access speed...\n";

    // 1. Тест std::bitset (Пункт в)
    auto start = high_resolution_clock::now();
    // volatile каже компілятору, щоб він не викидав змінну, навіть якщо вона йому здається зайвою.
    // Це потрібно, щоб цикл реально крутився, а не був оптимізований в нуль.
    volatile bool dummy = false;

    for(int i = 0; i < 1000000; i++) {
        Shop s("BenchItem", 10.0, "UA", true, false, true); // Створення на стеку (швидко)
        if(s.isAvailable()) dummy = !dummy;
    }
    auto end = high_resolution_clock::now();
    auto durationBitset = duration_cast<milliseconds>(end - start).count();

    cout << "1. std::bitset implementation: " << durationBitset << " ms\n";

    // 2. Тест std::vector<bool> (Пункт б)
    start = high_resolution_clock::now();
    for(int i = 0; i < 1000000; i++) {
        ShopVector s("BenchItem", 10.0, "UA", true, false, true); // Створення в купі (повільно)
        if(s.flags[0]) dummy = !dummy;
    }
    end = high_resolution_clock::now();
    auto durationVector = duration_cast<milliseconds>(end - start).count();

    cout << "2. std::vector<bool> implementation: " << durationVector << " ms\n";

    cout << "Result: bitset is approx " << (double)durationVector/durationBitset << "x faster.\n";

    char buffer[100];
    sprintf(buffer, "Benchmark: Bitset=%lld ms, Vector=%lld ms", durationBitset, durationVector);
    logResult(buffer);
}

// Тестуємо обидва варіанти (вектор і бітсет)
void testShopVariants(bool fromFile) {
    cout << "\n-- Task 1 --\n";
    vector<Shop> listBitset;
    vector<ShopVector> listVector;

    if (fromFile) {
        cout << "[INFO] Loading demo data...\n";
        listBitset.push_back(Shop("ItemBit", 100, "UA", 1, 1, 0));
        listVector.push_back(ShopVector("ItemVec", 100, "UA", 1, 1, 0));
    } else {
        Shop s;
        cout << "Enter data for Bitset implementation:\n";
        cin >> s;
        listBitset.push_back(s);
        // Копіюємо дані у векторний варіант
        listVector.push_back(ShopVector(s.name, s.price, s.country,
                                        s.isAvailable(), s.meetsEUStandard(), s.isProductOfMonth()));
    }

    cout << "Data loaded correctly.\n";
    logResult("Shop Task Completed");
}

void testNumbers() {
    cout << "\n-- Task 2 and 3 --\n";
    unsigned int n = 7;
    cout << "Num " << n << ": " << (NumberAnalyzer::isEven(n) ? "Even" : "Odd") << endl;
    logResult("Numbers Task Completed");
}

void testDateTime() {
    cout << "\n-- Task 4 --\n";
    CompactDateTime dt1(2024, 12, 1, 14, 0, 0);
    dt1.print(); cout << endl;
    logResult("DateTime Task Completed");
}

int main() {
    ofstream f("TestResult_CPP.txt");
    f << "CPP test report" << endl;
    f.close();

    int mode;
    cout << "Select Mode:\n1. Console\n2. File Simulation\n> ";
    if (!(cin >> mode)) mode = 2;

    testShopVariants(mode == 2);
    testNumbers();
    testDateTime();

    // Запускаємо порівняння швидкості
    runBenchmark();

    cout << "\nC++ Tests Finished.\n";
    return 0;
}