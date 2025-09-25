#include <stdio.h>
#include <stdarg.h>

void task1();
void task2();

int main() {
    int choice = 1;

    if (choice == 1) {
        task1();
    }
    else if (choice == 2) {
        task2();
    }
    else {
        printf("Invalid choice.\n");
    }

    return 0;
}

void task1() {
    printf("task1:\n");
    char str1[] = "Hello";
    char str2[] = "World";

    printf("!!! %s, %s! !!!\n", str1, str2);
}

void task2() {
    printf("task2:\n");
    float a, v, t, S;

    printf("Enter acceleration a: ");
    if (scanf_s("%f", &a) != 1) {
        printf("Error! Enter a valid number for acceleration.\n");
        return;
    }

    printf("Enter final velocity v: ");
    if (scanf_s("%f", &v) != 1) {
        printf("Error! Enter a valid number for velocity.\n");
        return;
    }

    t = v / a;
    S = (a * t * t) / 2;

    printf("\nTime of motion t = %.2f s\n", t);
    printf("Distance traveled S = %.2f m\n", S);
}
