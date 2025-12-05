/*
BitFields Project C++ - Header File
Student: Shakun Anastasia
Group: compmath, 2 course
Опис класів з використанням std::bitset та std::vector<bool>
*/

#ifndef BITFIELDS_HPP
#define BITFIELDS_HPP

#include <iostream>
#include <string>
#include <vector>
#include <bitset>

// Задача 1
class Shop {
public:
    std::string name;
    float price;
    std::string country;

    // std::bitset зберігається на стеку.
    // <3> - означає фіксований розмір 3 біти.
    std::bitset<3> flags;

    Shop() : price(0.0) {}
    Shop(std::string n, float p, std::string c, bool avail, bool eu, bool promo);

    // Гетери для зручного доступу до бітів
    bool isAvailable() const;
    bool meetsEUStandard() const;
    bool isProductOfMonth() const;

    // "friend" дозволяє оператору достукатися до приватних даних класу.
    // Перевантаження << дозволяє писати cout << shop;
    friend std::ostream& operator<<(std::ostream& os, const Shop& shop);
    friend std::istream& operator>>(std::istream& is, Shop& shop);
};

// Задача 1 з vector<bool>
class ShopVector {
public:
    std::string name;
    float price;
    std::string country;

    // vector<bool> - це динамічний масив. Він зберігається в купі (Heap).
    // Це повільніше, але розмір можна змінювати на ходу.
    std::vector<bool> flags;

    ShopVector() : price(0.0) {}
    ShopVector(std::string n, float p, std::string c, bool avail, bool eu, bool promo);

    friend std::ostream& operator<<(std::ostream& os, const ShopVector& shop);
};

// Задача 2 і 3
class NumberAnalyzer {
public:
    // static - методи можна викликати без створення об'єкта класу
    static bool isEven(unsigned int num);
    static bool isMultipleOf8(unsigned int num);
};

// Задача 4
class CompactDateTime {
private:
    // Пакуємо все в 64 біти. Це один long long int.
    std::bitset<64> data;
public:
    CompactDateTime(int year, int month, int day, int hour, int minute, int second);

    // Методи для "витягування" даних з бітів
    int getYear() const;
    int getMonth() const;
    int getDay() const;
    int getHour() const;
    int getMinute() const;
    int getSecond() const;

    void print() const;
    int toSeconds() const;
};

int timeDifference(const CompactDateTime& dt1, const CompactDateTime& dt2);

#endif // BITFIELDS_HPP