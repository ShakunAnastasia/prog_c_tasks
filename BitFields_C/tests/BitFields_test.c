/*
BitFields Project - Test File & Entry Point
Student: Shakun Anastasia
Group: compmath, 2 course
Тестовий файл: Меню, введення з файлу/консолі, вивід у файл.
*/

#include <stdio.h>
#include <stdlib.h>
#include "../src/BitFields.h"

// Функція для запису результатів у файл (щоб виконати вимогу про звіт)
void logResult(const char* msg) {
    FILE *f = fopen("TestResult.txt", "a"); // "a" - append (дописуємо в кінець)
    if (f) {
        fprintf(f, "%s\n", msg);
        fclose(f);
    }
}

// Тестування структури Магазин
void runTask1_Shop(int fromFile) {
    struct Shop products[MAX_PRODUCTS];
    // Тимчасові змінні потрібні, бо fscanf не вміє писати прямо в бітові поля (: 1)
    unsigned int temp1, temp2, temp3;

    printf("\n-- Task 1 : shop --\n");

    if (fromFile) {
        FILE *f = fopen("BitFields_test.txt", "r");
        if (!f) {
            printf("Error: Cannot open BitFields_test.txt. Using demo data.\n");
            // Якщо файлу немає, заповнюємо демо-даними (симуляція)
            struct Shop demo[MAX_PRODUCTS] = {
                {"FileItem1", 10.5, "USA", 1, 1, 0},
                {"FileItem2", 20.0, "UA", 1, 0, 1},
                {"FileItem3", 30.0, "DE", 0, 1, 0},
                {"FileItem4", 40.0, "PL", 1, 0, 0},
                {"FileItem5", 50.0, "CN", 1, 1, 1}
            };
            for(int i=0; i<MAX_PRODUCTS; i++) products[i] = demo[i];
        } else {
            // Читаємо з файлу
            for(int i=0; i<MAX_PRODUCTS; i++) {
                // Читаємо в temp змінні, а потім присвоюємо в поля
                if(fscanf(f, "%s %f %s %u %u %u",
                    products[i].name, &products[i].price, products[i].country,
                    &temp1, &temp2, &temp3) == 6) {
                        products[i].isAvailable = temp1;
                        products[i].meetsEUStandard = temp2;
                        products[i].isProductOfMonth = temp3;
                }
            }
            fclose(f);
        }
    } else {
        // Ввід з консолі
        printf("Please enter data for %d products:\n", MAX_PRODUCTS);
        for (int i = 0; i < MAX_PRODUCTS; i++) {
            printf("\nProduct #%d:\n", i + 1);
            inputShopData(&products[i]);
        }
    }

    printAllGoods(products, MAX_PRODUCTS);
    printNonEUGoods(products, MAX_PRODUCTS);

    logResult("Task 1 Shop: Completed");
}

// Тестування бітового аналізу (парність/кратність)
void runTask2_3_Numbers() {
    printf("\n-- Task 2 and 3 --\n");
    unsigned int nums[] = {4, 7, 15, 16, 24};
    char buffer[100];

    for(int i=0; i<5; i++) {
        int isEven = isEvenBitField(nums[i]);
        int isMod8 = isMultipleOf8BitField(nums[i]);

        printf("Number %u: %s, %s multiple of 8\n",
               nums[i],
               isEven ? "EVEN" : "ODD",
               isMod8 ? "IS" : "NOT");

        sprintf(buffer, "Num %u: Even=%d, Mod8=%d", nums[i], isEven, isMod8);
        logResult(buffer);
    }
}

// Тестування дати
void runTask4_DateTime() {
    printf("\n-- Task 4 --\n");
    struct CompactDateTime dt1, dt2;
    // Ініціалізація тестовими даними
    initDateTime(&dt1, 2024, 12, 1, 10, 0, 0);
    initDateTime(&dt2, 2024, 12, 1, 12, 30, 0);

    printf("DT1: "); printDateTime(&dt1); printf("\n");
    printf("DT2: "); printDateTime(&dt2); printf("\n");

    int diff = timeDifference(&dt2, &dt1);
    printf("Difference in seconds: %d\n", diff);

    char buffer[100];
    sprintf(buffer, "Task 4 Diff: %d sec", diff);
    logResult(buffer);
}

int main() {
    // Очистимо файл результатів на початку запуску
    FILE *f = fopen("TestResult.txt", "w");
    if(f) { fprintf(f, " - Test report -\n"); fclose(f); }

    int mode;
    printf("Select Mode:\n1. Console Input\n2. File Input (Simulation)\n> ");
    if (scanf("%d", &mode) != 1) mode = 2; // Захист від неправильного вводу
    clearInputBuffer();

    int fromFile = (mode == 2);

    runTask1_Shop(fromFile);
    runTask2_3_Numbers();
    runTask4_DateTime();

    printf("\nTests finished. Results saved to TestResult.txt\n");
    return 0;
}