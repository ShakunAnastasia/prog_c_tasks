/*
BitFields Project - Header File
Student: Shakun Anastasia
Group: compmath, 2 course
Заголовочний файл з оголошеннями структур
*/

#ifndef BITFIELDS_H
#define BITFIELDS_H

#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 5

// Задача 1
struct Shop {
    char name[50];
    float price;
    char country[30];
    // Бітові поля. Конструкція ": 1" каже компілятору виділити рівно 1 біт.
    // Всі три змінні будуть упаковані в один байт (або слово), економлячи пам'ять.
    unsigned int isAvailable : 1;      // 1 біт (0 або 1)
    unsigned int meetsEUStandard : 1;  // 1 біт
    unsigned int isProductOfMonth : 1; // 1 біт
};

// Задача 2 і 3
// Union (Об'єднання) дозволяє зберігати різні дані в одній і тій самій ділянці пам'яті.
// Ми можемо звернутися до 'number' як до числа, або до 'bits' як до набору бітів.
union NumberAnalyzer {
    unsigned int number;
    struct {
        unsigned int bit0 : 1; // LSB (Молодший біт) - відповідає за парність (1, 3, 5...)
        unsigned int bit1 : 1; // 2-й біт (число 2)
        unsigned int bit2 : 1; // 3-й біт (число 4)
        // Інші біти нам явно не потрібні для цих задач, але заповнимо до 32 біт
        unsigned int others : 29;
    } bits;
};

// Задача 4
// Замість 6 int-ів (24 байти), ми пакуємо все в біти.
struct CompactDateTime {
    unsigned int year : 12;   // 0-4095 (достатньо для зберігання року)
    unsigned int month : 4;   // 1-12 (влізає в 4 біти, бо 2^4 = 16)
    unsigned int day : 5;     // 1-31 (влізає в 5 біт, бо 2^5 = 32)
    unsigned int hour : 5;    // 0-23
    unsigned int minute : 6;  // 0-59 (влізає в 6 біт, бо 2^6 = 64)
    unsigned int second : 6;  // 0-59
};

// Прототипи функцій (обіцянки компілятору, що такі функції існують)
void inputShopData(struct Shop* shop);
void printShopInfo(const struct Shop* shop);
void printAllGoods(const struct Shop* goods, int count);
void printNonEUGoods(const struct Shop* goods, int count);

int isEvenBitField(unsigned int num);
int isMultipleOf8BitField(unsigned int num);

void initDateTime(struct CompactDateTime* dt, int year, int month, int day, int hour, int minute, int second);
int timeDifference(const struct CompactDateTime* dt1, const struct CompactDateTime* dt2);
void printDateTime(const struct CompactDateTime* dt);

void clearInputBuffer();

#endif // BITFIELDS_H