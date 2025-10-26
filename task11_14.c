#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#define MAX_NAME 50
#define MAX_TOYS 100

typedef struct {
    char name[MAX_NAME];
    double price;
    int min_age;
    int max_age;
} Toy;

Toy toys[MAX_TOYS];
int toy_count = 0;

void loadToys(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file %s\n", filename);
        return;
    }

    toy_count = 0;
    while (fscanf(file, "%s %lf %d %d",
        toys[toy_count].name,
        &toys[toy_count].price,
        &toys[toy_count].min_age,
        &toys[toy_count].max_age) == 4) {
        toy_count++;
        if (toy_count >= MAX_TOYS) break;
    }
    fclose(file);
    printf("Loaded %d toys\n", toy_count);
}

void saveToBinary(const char* filename, Toy* result, int count) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        printf("Error creating binary file\n");
        return;
    }

    fwrite(&count, sizeof(int), 1, file);
    for (int i = 0; i < count; i++) {
        fwrite(&result[i], sizeof(Toy), 1, file);
    }
    fclose(file);
}

void printToys(Toy* result, int count, const char* message) {
    printf("%s:\n", message);
    if (count == 0) {
        printf("  No toys found\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        printf("  %s - %.2f UAH, age: %d-%d years\n",
            result[i].name, result[i].price,
            result[i].min_age, result[i].max_age);
    }
}

void taskA(double max_price) {
    Toy result[MAX_TOYS];
    int count = 0;

    for (int i = 0; i < toy_count; i++) {
        if (toys[i].price <= max_price &&
            toys[i].min_age <= 5 && toys[i].max_age >= 5) {
            result[count++] = toys[i];
        }
    }

    saveToBinary("taskA.bin", result, count);
    printToys(result, count, "a) Toys under price for age 5");
}

void taskB(int n, int m) {
    Toy result[MAX_TOYS];
    int count = 0;

    for (int i = 0; i < toy_count; i++) {
        if (toys[i].min_age <= n && toys[i].max_age >= n &&
            toys[i].min_age <= m && toys[i].max_age >= m) {
            result[count++] = toys[i];
        }
    }

    saveToBinary("taskB.bin", result, count);
    printToys(result, count, "b) Toys for both ages");
}

void taskC(double a) {
    if (toy_count == 0) return;

    double max_price = 0;
    for (int i = 0; i < toy_count; i++) {
        if (toys[i].price > max_price) {
            max_price = toys[i].price;
        }
    }

    Toy result[MAX_TOYS];
    int count = 0;

    for (int i = 0; i < toy_count; i++) {
        if (max_price - toys[i].price <= a) {
            result[count++] = toys[i];
        }
    }

    saveToBinary("taskC.bin", result, count);
    printToys(result, count, "c) Most expensive toys");
}

void taskD(const char* name) {
    double max_price = 0;
    int found = 0;

    for (int i = 0; i < toy_count; i++) {
        if (strcmp(toys[i].name, name) == 0 && toys[i].price > max_price) {
            max_price = toys[i].price;
            found = 1;
        }
    }

    printf("d) Max price for %s: ", name);
    if (found) {
        printf("%.2f UAH\n", max_price);
    }
    else {
        printf("Not found\n");
    }
}

void taskE(const char* name) {
    double total = 0;
    int count = 0;

    for (int i = 0; i < toy_count; i++) {
        if (strcmp(toys[i].name, name) == 0) {
            total += toys[i].price;
            count++;
        }
    }

    printf("e) Total price for %s: ", name);
    if (count > 0) {
        printf("%.2f UAH (%d items)\n", total, count);
    }
    else {
        printf("Not found\n");
    }
}

void taskF(int x, double Y) {
    Toy result[2];
    int found = 0;

    for (int i = 0; i < toy_count - 1 && !found; i++) {
        if (toys[i].min_age <= x && toys[i].max_age >= x) {
            for (int j = i + 1; j < toy_count && !found; j++) {
                if (toys[j].min_age <= x && toys[j].max_age >= x &&
                    toys[i].price + toys[j].price <= Y) {
                    result[0] = toys[i];
                    result[1] = toys[j];
                    found = 1;
                }
            }
        }
    }

    printf("f) Two toys for age %d under %.2f UAH: ", x, Y);
    if (found) {
        printf("%s (%.2f) + %s (%.2f) = %.2f UAH\n",
            result[0].name, result[0].price,
            result[1].name, result[1].price,
            result[0].price + result[1].price);
    }
    else {
        printf("Not found\n");
    }
}

void taskG(double Y, int x) {
    int found = 0;

    for (int i = 0; i < toy_count; i++) {
        if (strcmp(toys[i].name, "constructor") == 0 &&
            toys[i].price == Y &&
            toys[i].min_age <= x && toys[i].max_age >= 12) {
            printf("g) Constructor found: %.2f UAH, age %d-12 years\n", Y, x);
            found = 1;
            break;
        }
    }

    if (!found) {
        FILE* file = fopen("no_constructor.txt", "w");
        if (file) {
            fprintf(file, "Constructor with price %.2f for age %d-12 not found", Y, x);
            fclose(file);
        }
        printf("g) Constructor not found - info saved to file\n");
    }
}

int main() {
    loadToys("toys.txt");

    if (toy_count == 0) {
        printf("No toys loaded\n");
        return 1;
    }

    taskA(100.0);
    taskB(3, 5);
    taskC(10.0);
    taskD("ball");
    taskE("doll");
    taskF(4, 150.0);
    taskG(200.0, 6);

    return 0;
}