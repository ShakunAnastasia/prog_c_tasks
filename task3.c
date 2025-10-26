#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

#define F_FILENAME "F_numbers.dat"
#define G_FILENAME "G_numbers.dat"

bool isEven(int num);
bool isPowerOfThree(int num);
bool isPerfectSquare(int num);
bool hasExactlyThreeDivisors(int num);
bool isPalindrome(int num);
bool isFibonacci(int num);
int createFileF();
void createFileG();
void displayFileContents(const char* filename, const char* description);

bool isEven(int num) {
    return num % 2 == 0;
}

bool isPowerOfThree(int num) {
    if (num <= 0) return false;
    while (num % 3 == 0) {
        num /= 3;
    }
    return num == 1;
}

bool isPerfectSquare(int num) {
    if (num < 0) return false;
    int root = (int)sqrt(num);
    return root * root == num;
}

bool hasExactlyThreeDivisors(int num) {
    if (num <= 1) return false;

    int root = (int)sqrt(num);
    if (root * root != num) return false;

    if (root < 2) return false;
    for (int i = 2; i * i <= root; i++) {
        if (root % i == 0) return false;
    }
    return true;
}

bool isPalindrome(int num) {
    if (num < 0) return false;

    int original = num;
    int reversed = 0;

    while (num > 0) {
        reversed = reversed * 10 + num % 10;
        num /= 10;
    }

    return original == reversed;
}

bool isFibonacci(int num) {
    if (num < 0) return false;
    if (num == 0 || num == 1) return true;

    long long check1 = 5LL * num * num + 4;
    long long check2 = 5LL * num * num - 4;

    long long root1 = (long long)sqrt(check1);
    long long root2 = (long long)sqrt(check2);

    return (root1 * root1 == check1) || (root2 * root2 == check2);
}

int createFileF() {
    printf("Creating File F...\n");
    printf("Enter integers (0 to stop):\n");

    FILE* file = fopen(F_FILENAME, "wb");
    if (file == NULL) {
        printf("Error: Cannot create file '%s'\n", F_FILENAME);
        return -1;
    }

    int number;
    int count = 0;

    while (true) {
        printf("Enter number %d: ", count + 1);

        if (scanf_s("%d", &number) != 1) {
            printf("Error: Invalid input. Please enter an integer.\n");
            while (getchar() != '\n');
            continue;
        }

        if (number == 0) {
            break;
        }

        if (fwrite(&number, sizeof(int), 1, file) != 1) {
            printf("Error: Failed to write number to file\n");
            fclose(file);
            return -1;
        }

        count++;
    }

    fclose(file);
    printf("Successfully wrote %d numbers to file '%s'\n\n", count, F_FILENAME);
    return count;
}

void createFileG() {
    printf("Creating File G based on criteria...\n");

    FILE* fileF = fopen(F_FILENAME, "rb");
    if (fileF == NULL) {
        printf("Error: Cannot open file '%s' for reading\n", F_FILENAME);
        return;
    }

    FILE* fileG = fopen(G_FILENAME, "wb");
    if (fileG == NULL) {
        printf("Error: Cannot create file '%s'\n", G_FILENAME);
        fclose(fileF);
        return;
    }

    int number;
    int totalCount = 0;
    int criteriaCount[6] = { 0 };

    printf("\nProcessing numbers from file F:\n");

    while (fread(&number, sizeof(int), 1, fileF) == 1) {
        printf("Number: %d - ", number);
        bool meetsAnyCriteria = false;

        if (isEven(number)) {
            printf("Even ");
            if (!meetsAnyCriteria) {
                fwrite(&number, sizeof(int), 1, fileG);
                totalCount++;
                meetsAnyCriteria = true;
            }
            criteriaCount[0]++;
        }

        if (isPowerOfThree(number)) {
            printf("PowerOf3 ");
            if (!meetsAnyCriteria) {
                fwrite(&number, sizeof(int), 1, fileG);
                totalCount++;
                meetsAnyCriteria = true;
            }
            criteriaCount[1]++;
        }

        if (isPerfectSquare(number)) {
            printf("PerfectSquare ");
            if (!meetsAnyCriteria) {
                fwrite(&number, sizeof(int), 1, fileG);
                totalCount++;
                meetsAnyCriteria = true;
            }
            criteriaCount[2]++;
        }

        if (hasExactlyThreeDivisors(number)) {
            printf("3Divisors ");
            if (!meetsAnyCriteria) {
                fwrite(&number, sizeof(int), 1, fileG);
                totalCount++;
                meetsAnyCriteria = true;
            }
            criteriaCount[3]++;
        }

        if (isPalindrome(number)) {
            printf("Palindrome ");
            if (!meetsAnyCriteria) {
                fwrite(&number, sizeof(int), 1, fileG);
                totalCount++;
                meetsAnyCriteria = true;
            }
            criteriaCount[4]++;
        }

        if (isFibonacci(number)) {
            printf("Fibonacci ");
            if (!meetsAnyCriteria) {
                fwrite(&number, sizeof(int), 1, fileG);
                totalCount++;
                meetsAnyCriteria = true;
            }
            criteriaCount[5]++;
        }

        if (!meetsAnyCriteria) {
            printf("No criteria matched");
        }
        printf("\n");
    }

    fclose(fileF);
    fclose(fileG);

    printf("\nCriteria Statistics:\n");
    printf("a) Even numbers: %d\n", criteriaCount[0]);
    printf("b) Powers of 3: %d\n", criteriaCount[1]);
    printf("c) Perfect squares: %d\n", criteriaCount[2]);
    printf("d) Numbers with exactly 3 divisors: %d\n", criteriaCount[3]);
    printf("e) Palindromes: %d\n", criteriaCount[4]);
    printf("f) Fibonacci numbers: %d\n", criteriaCount[5]);
    printf("Total unique numbers written to file G: %d\n\n", totalCount);
}

void displayFileContents(const char* filename, const char* description) {
    printf("%s\n", description);

    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error: Cannot open file '%s'\n", filename);
        return;
    }

    int number;
    int count = 0;

    printf("Contents: ");
    while (fread(&number, sizeof(int), 1, file) == 1) {
        printf("%d ", number);
        count++;
    }

    printf("\nTotal numbers: %d\n\n", count);
    fclose(file);
}

void demonstrateCriteria() {
    printf("Criteria Demonstration\n");

    int testNumbers[] = { 2, 3, 4, 9, 16, 25, 121, 144, 81, 13, 21, 8, 27 };
    int testCount = sizeof(testNumbers) / sizeof(testNumbers[0]);

    printf("Testing criteria on sample numbers:\n");
    for (int i = 0; i < testCount; i++) {
        int num = testNumbers[i];
        printf("%3d: ", num);

        if (isEven(num)) printf("Even ");
        if (isPowerOfThree(num)) printf("Power3 ");
        if (isPerfectSquare(num)) printf("Square ");
        if (hasExactlyThreeDivisors(num)) printf("3Div ");
        if (isPalindrome(num)) printf("Palindrome ");
        if (isFibonacci(num)) printf("Fibonacci ");

        printf("\n");
    }
    printf("\n");
}

int main() {
    printf("File Operations: Filtering Numbers by Criteria\n");
    demonstrateCriteria();

    if (createFileF() <= 0) {
        printf("No numbers entered or error occurred. Exiting.\n");
        return EXIT_FAILURE;
    }

    displayFileContents(F_FILENAME, "File F Contents");

    createFileG();

    displayFileContents(G_FILENAME, "File G Contents (Numbers meeting criteria)");

    printf("Program completed successfully!\n");
    return EXIT_SUCCESS;
}