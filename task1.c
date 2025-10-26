#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void write_array_to_file(double arr[], int n, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Cannot open file %s for writing.\n", filename);
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(file, "%.2lf", arr[i]);
        if (i < n - 1) {
            fprintf(file, " ");
        }
    }

    fclose(file);
    printf("Array successfully written to file '%s'\n", filename);
}

void print_file_contents(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Cannot open file %s for reading.\n", filename);
        return;
    }

    printf("File contents: ");
    double number;
    int first = 1;

    while (fscanf(file, "%lf", &number) == 1) {
        if (!first) {
            printf(", ");
        }
        printf("%.2lf", number);
        first = 0;
    }

    printf("\n");
    fclose(file);
}

int main() {
    int n;
    char filename[100];

    printf("Task 1.\n\n");

    printf("Enter array length: ");
    while (scanf("%d", &n) != 1 || n <= 0) {
        printf("Error: Length must be positive integer. Try again: ");
        while (getchar() != '\n');
    }

    double* arr = (double*)malloc(n * sizeof(double));
    if (arr == NULL) {
        printf("Error: Memory allocation failed!\n");
        return 1;
    }

    printf("Enter %d real numbers:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Element %d: ", i + 1);
        while (scanf("%lf", &arr[i]) != 1) {
            printf("Error: Please enter a valid real number. Try again: ");
            while (getchar() != '\n');
        }
    }

    printf("Enter filename: ");
    scanf_s("%99s", filename, (unsigned)sizeof(filename));

    write_array_to_file(arr, n, filename);

    printf("\n");
    print_file_contents(filename);

    free(arr);

    printf("\nProgram completed successfully.\n");
    return 0;
}