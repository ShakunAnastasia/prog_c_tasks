/*
BitFields Cross Test
Student: Shakun Anastasia
Порівняння реалізацій C та C++
*/

#include <iostream>
#include <cassert>
#include "../src/BitFields.hpp" // C++ Header

// extern "C" потрібен, щоб C++ компілятор зрозумів, що ці функції
// скомпільовані компілятором C (там інші правила іменування в об'єктному файлі).
// Без цього буде помилка.
extern "C" {
    int isEvenBitField(unsigned int num);
    int isMultipleOf8BitField(unsigned int num);
}

int main() {
    std::cout << "-- cross test : C vs CPP --\n";

    unsigned int testVals[] = {4, 5, 8, 16, 33, 100};

    for(unsigned int val : testVals) {
        // 1. Викликаємо функцію з C (isEvenBitField)
        bool c_even = isEvenBitField(val);
        // 2. Викликаємо функцію з C++ (NumberAnalyzer::isEven)
        bool cpp_even = NumberAnalyzer::isEven(val);

        std::cout << "Val " << val << ": C_Even=" << c_even << " CPP_Even=" << cpp_even;

        // Порівнюємо результати
        if (c_even == cpp_even) std::cout << " [MATCH]\n";
        else { std::cout << " [FAIL]\n"; return 1; }

        // Те саме для кратності 8
        bool c_mod8 = isMultipleOf8BitField(val);
        bool cpp_mod8 = NumberAnalyzer::isMultipleOf8(val);

        if (c_mod8 != cpp_mod8) {
            std::cout << "Mismatch in Mod8 for " << val << "\n";
            return 1;
        }
    }

    std::cout << "\nAll cross test passed! Logic is identical.\n";
    return 0;
}