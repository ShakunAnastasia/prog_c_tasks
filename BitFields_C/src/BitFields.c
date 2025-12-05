/*
BitFields Project - Implementation File
Student: Shakun Anastasia
Group: compmath, 2 course
Файл реалізації функцій
*/

#include "BitFields.h"
#include <string.h> // Потрібно для strcspn (обробка рядків)

// Доп функція (після сканф залишається у буфері клавіатури \n і наступна функція може спіткнутися і прочитати
// наступний пустий рядом
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Shop
// Вивід одного товару
void printShopInfo(const struct Shop* shop) {
    // оформлення таблички : %-15s - вирівнювання тексту вліво на 15 символів;
    // %d використовується для бітових полів, бо компілятор автоматично перетворює їх в int
    printf("Product: %-15s | Price: %7.2f | Country: %-10s | Stock: %d | EU: %d | Promo: %d\n",
           shop->name, shop->price, shop->country,
           shop->isAvailable, shop->meetsEUStandard, shop->isProductOfMonth);
}

// Введення даних про товар
void inputShopData(struct Shop* shop) {
    printf("Enter product name: ");
    // fgets безпечніший за gets, бо ми вказуємо розмір буфера
    fgets(shop->name, sizeof(shop->name), stdin);
    // fgets зберігає натискання \n, функція strcspn знаходить цей \n і замінює його на 0 (кінець рядка).
    shop->name[strcspn(shop->name, "\n")] = 0;

    printf("Enter price: ");
    scanf("%f", &shop->price);
    clearInputBuffer(); // Очищаємо \n

    printf("Enter country: ");
    fgets(shop->country, sizeof(shop->country), stdin);
    shop->country[strcspn(shop->country, "\n")] = 0;

    unsigned int temp; // Тимчасова змінна, бо ми и не можемо робити scanf напряму в бітове поле, бо scanf вимагає адресу (&),
// а бітове поле не має власної адреси.

    printf("Is available (1-Yes, 0-No): ");
    scanf("%u", &temp);
    // ВАЖЛИВО: (temp & 1) - це бітова маска ( не важлтво що юзер вводить, ми беремо тільки останній біт (це захист від переповнення бітового поля)
    shop->isAvailable = temp & 1;

    printf("Meets EU standard (1-Yes, 0-No): ");
    scanf("%u", &temp);
    shop->meetsEUStandard = temp & 1; // Аналогічно, беремо тільки молодший біт

    printf("Is product of month (1-Yes, 0-No): ");
    scanf("%u", &temp);
    shop->isProductOfMonth = temp & 1;

    clearInputBuffer();
}

// Вивід усіх товарів
void printAllGoods(const struct Shop* goods, int count) {
    printf("\n-- ALL PRODUCTS --\n");
    for (int i = 0; i < count; i++) {
        printf("#%d: ", i + 1);
        printShopInfo(&goods[i]); // Передаємо адресу елемента масиву
    }
}

// Фільтрація: Товари в наявності, але не стандарту EU
void printNonEUGoods(const struct Shop* goods, int count) {
    printf("\n-- NON-EU PRODUCTS IN STOCK --\n");
    int found = 0;
    for (int i = 0; i < count; i++) {
        // Перевірка умови: "Є в наявності" і "не відповідає стандарту"
        if (goods[i].isAvailable && !goods[i].meetsEUStandard) {
            printShopInfo(&goods[i]);
            found = 1;
        }
    }
    if (!found) printf("No matching products found.\n");
}

// Залача 2
// Мета: перевірити парність
int isEvenBitField(unsigned int num) {
    union NumberAnalyzer analyzer; // Використовуємо Union
    analyzer.number = num;

    // Парність залежить тільки від молодшого біта (bit0).
    // 0 - парне, 1 - непарне.
    return analyzer.bits.bit0 == 0;
}

// Задача 3
// Мета: перевірити кратність 8
int isMultipleOf8BitField(unsigned int num) {
    union NumberAnalyzer analyzer;
    analyzer.number = num;

    // Число ділиться на 8 (2^3), якщо воно закінчується на три нулі (...000)
    // Тобто 1-й, 2-й та 4-й біти мають бути нулями.
    return (analyzer.bits.bit0 == 0) &&
           (analyzer.bits.bit1 == 0) &&
           (analyzer.bits.bit2 == 0);
}

// Задача 4
// Упаковка даних у бітові поля
void initDateTime(struct CompactDateTime* dt, int year, int month, int day, int hour, int minute, int second) {
    // Ми виділили під рік всього 12 біт (макс число 4095).
    // Щоб зекономити місце, ми зберігаємо не 2024, а просто 24.
    dt->year = (year > 2000) ? (year - 2000) : 0;
    dt->month = month;
    dt->day = day;
    dt->hour = hour;
    dt->minute = minute;
    dt->second = second;
}

// Розрахунок різниці в часі
int timeDifference(const struct CompactDateTime* dt1, const struct CompactDateTime* dt2) {
    // Переводимо час в секунди від початку доби
    int s1 = dt1->hour * 3600 + dt1->minute * 60 + dt1->second;
    int s2 = dt2->hour * 3600 + dt2->minute * 60 + dt2->second;
    return s1 - s2;
}

// Вивід дати (розпаковка)
void printDateTime(const struct CompactDateTime* dt) {
    // При виводі додаємо 2000 назад, щоб отримати повний рік
    printf("%02u.%02u.%04u %02u:%02u:%02u",
           dt->day, dt->month, dt->year + 2000,
           dt->hour, dt->minute, dt->second);
}