#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void create_file_F() {
    FILE* file = fopen("F.txt", "w");
    if (file == NULL) {
        printf("Error: Cannot create file F.txt\n");
        return;
    }

    int n;
    printf("Enter number of real numbers for file F: ");
    while (scanf("%d", &n) != 1 || n <= 0) {
        printf("Error: Enter a positive integer: ");
        while (getchar() != '\n');
    }

    printf("Enter %d real numbers:\n", n);
    for (int i = 0; i < n; i++) {
        double num;
        printf("Number %d: ", i + 1);
        while (scanf("%lf", &num) != 1) {
            printf("Error: Enter a real number: ");
            while (getchar() != '\n');
        }
        fprintf(file, "%.2lf\n", num);
    }

    fclose(file);
    printf("File F created successfully with %d numbers.\n", n);
}

void create_file_G(double a) {
    FILE* fileF = fopen("F.txt", "r");
    FILE* fileG = fopen("G.txt", "w");

    if (fileF == NULL || fileG == NULL) {
        printf("Error: Cannot open files\n");
        if (fileF) fclose(fileF);
        if (fileG) fclose(fileG);
        return;
    }

    double number;
    int count = 0;

    printf("\nNumbers written to file G (|x| < %.2lf): ", a);
    while (fscanf(fileF, "%lf", &number) == 1) {
        if (fabs(number) < a) {
            fprintf(fileG, "%.2lf\n", number);
            printf("%.2lf ", number);
            count++;
        }
    }

    printf("\nTotal %d numbers written to file G.\n", count);

    fclose(fileF);
    fclose(fileG);
}

void remove_from_file_F(double a) {
    FILE* fileF = fopen("F.txt", "r");
    if (fileF == NULL) {
        printf("Error: Cannot open file F.txt\n");
        return;
    }

    double* numbers = NULL;
    int count = 0;
    int capacity = 10;
    numbers = (double*)malloc(capacity * sizeof(double));
    if (!numbers) {
        printf("Error: Memory allocation failed\n");
        fclose(fileF);
        return;
    }

    double number;
    while (fscanf(fileF, "%lf", &number) == 1) {
        if (fabs(number) >= a) {
            if (count == capacity) {
                capacity *= 2;
                double* temp = (double*)realloc(numbers, capacity * sizeof(double));
                if (!temp) {
                    printf("Error: Memory allocation failed\n");
                    free(numbers);
                    fclose(fileF);
                    return;
                }
                numbers = temp;
            }
            numbers[count++] = number;
        }
    }
    fclose(fileF);

    fileF = fopen("F.txt", "w");
    if (fileF == NULL) {
        printf("Error: Cannot rewrite file F.txt\n");
        free(numbers);
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fileF, "%.2lf\n", numbers[i]);
    }
    fclose(fileF);
    free(numbers);

    printf("Removed numbers with |x| < %.2lf from file F. %d numbers remaining.\n", a, count);
}

void display_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Cannot open file %s\n", filename);
        return;
    }

    printf("Contents of %s: ", filename);
    double number;
    int first = 1;

    while (fscanf(file, "%lf", &number) == 1) {
        if (!first) {
            printf(", ");
        }
        printf("%.2lf", number);
        first = 0;
    }

    if (first) {
        printf("(empty)");
    }
    printf("\n");

    fclose(file);
}

int main() {
    double a;

    printf("Task 2.\n\n");

    create_file_F();

    printf("\nEnter value a (a > 0): ");
    while (scanf("%lf", &a) != 1 || a <= 0) {
        printf("Error: a must be > 0. Try again: ");
        while (getchar() != '\n');
    }

    printf("\n Creating file G \n");
    display_file("F.txt");
    create_file_G(a);
    display_file("G.txt");

    printf("\n Removing from file F\n");
    remove_from_file_F(a);
    display_file("F.txt");

    printf("\nOperation completed successfully!\n");
    return 0;
}