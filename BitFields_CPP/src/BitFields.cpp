/*
BitFields Project C++ - Implementation
Student: Shakun Anastasia
Group: compmath, 2 course
*/

#include "BitFields.hpp"
#include <iomanip> // Для setw (форматування виводу)

// Shop з bitset
Shop::Shop(std::string n, float p, std::string c, bool avail, bool eu, bool promo)
    : name(n), price(p), country(c) {
    // Заповнюємо бітсет по індексах
    flags[0] = avail;
    flags[1] = eu;
    flags[2] = promo;
}

bool Shop::isAvailable() const { return flags[0]; }
bool Shop::meetsEUStandard() const { return flags[1]; }
bool Shop::isProductOfMonth() const { return flags[2]; }

// Перевантаження оператора << для виводу
std::ostream& operator<<(std::ostream& os, const Shop& shop) {
    os << "[Bitset] Product: " << std::setw(10) << std::left << shop.name
       << " | " << (shop.flags[0] ? "Stock" : "No   ") // Для краси
       << " | " << (shop.flags[1] ? "EU " : "Non-EU");
    return os;
}

// Перевантаження оператора >> для вводу (cin >> shop)
std::istream& operator>>(std::istream& is, Shop& shop) {
    std::cout << "Name: "; is >> shop.name;
    std::cout << "Price: "; is >> shop.price;
    std::cout << "Country: "; is >> shop.country;
    bool v;
    std::cout << "Available (1/0): "; is >> v; shop.flags[0] = v;
    std::cout << "EU Std (1/0): "; is >> v; shop.flags[1] = v;
    std::cout << "Promo (1/0): "; is >> v; shop.flags[2] = v;
    return is;
}

// Shop з vector <bool
ShopVector::ShopVector(std::string n, float p, std::string c, bool avail, bool eu, bool promo)
    : name(n), price(p), country(c) {
    // Вектор динамічний, тому використовуємо push_back
    flags.push_back(avail); // index 0
    flags.push_back(eu);    // index 1
    flags.push_back(promo); // index 2
}

std::ostream& operator<<(std::ostream& os, const ShopVector& shop) {
    // Доступ такий самий, як у масиву, через []
    os << "[Vector] Product: " << std::setw(10) << std::left << shop.name
       << " | " << (shop.flags[0] ? "Stock" : "No   ")
       << " | " << (shop.flags[1] ? "EU " : "Non-EU");
    return os;
}

// Number analyzer
bool NumberAnalyzer::isEven(unsigned int num) {
    std::bitset<32> bits(num); // Перетворюємо число в набір бітів
    return bits[0] == 0; // Перевіряємо молодший біт
}
bool NumberAnalyzer::isMultipleOf8(unsigned int num) {
    std::bitset<32> bits(num);
    // Кратність 8 = останні три біти нулі
    return !bits[0] && !bits[1] && !bits[2];
}

// Data implementation
// Допоміжна: записує значення value в біти, починаючи з startBit
void setBits(std::bitset<64>& b, int value, int startBit, int length) {
    for(int i = 0; i < length; i++) {
        // (value >> i) & 1  -- це маска, беремо і-тий біт числа
        b[startBit + i] = (value >> i) & 1;
    }
}
// Допоміжна: читає число з бітів
int getBits(const std::bitset<64>& b, int startBit, int length) {
    int value = 0;
    for(int i = 0; i < length; i++) {
        // Відновлюємо число: якщо біт є, додаємо 2 в степені i
        if(b[startBit + i]) value |= (1 << i);
    }
    return value;
}

CompactDateTime::CompactDateTime(int year, int month, int day, int hour, int minute, int second) {
    int y = (year > 2000) ? year - 2000 : 0;
    // Пакуємо дані по черзі
    setBits(data, second, 0, 6);
    setBits(data, minute, 6, 6);
    setBits(data, hour, 12, 5);
    setBits(data, day, 17, 5);
    setBits(data, month, 22, 4);
    setBits(data, y, 26, 12);
}

// Гетери просто викликають getBits з правильними зсувами
int CompactDateTime::getYear() const { return getBits(data, 26, 12) + 2000; }
int CompactDateTime::getMonth() const { return getBits(data, 22, 4); }
int CompactDateTime::getDay() const { return getBits(data, 17, 5); }
int CompactDateTime::getHour() const { return getBits(data, 12, 5); }
int CompactDateTime::getMinute() const { return getBits(data, 6, 6); }
int CompactDateTime::getSecond() const { return getBits(data, 0, 6); }

void CompactDateTime::print() const {
    std::cout << getDay() << "." << getMonth() << "." << getYear() << " "
              << getHour() << ":" << getMinute() << ":" << getSecond();
}
int CompactDateTime::toSeconds() const {
    return getHour() * 3600 + getMinute() * 60 + getSecond();
}
int timeDifference(const CompactDateTime& dt1, const CompactDateTime& dt2) {
    return dt1.toSeconds() - dt2.toSeconds();
}