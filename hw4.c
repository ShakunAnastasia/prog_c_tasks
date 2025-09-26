#include <stdio.h>
#include <math.h>

void task12();
void task24();

int main() {
    int choice;
	printf("Choose a task (12 or 24): ");
	scanf_s("%d", &choice);
	switch (choice) {
        case 12: task12(); break;
        case 24: task24(); break;
        default:
            printf("Invalid choice. Please choose 12 or 24.\n");
    }
    return 0;
}



void task12() {
    int n;
    double x;

    printf("Enter n: ");
    scanf_s("%d", &n);
    printf("Enter x: ");
    scanf_s("%lf", &x);

    if (n <= 0) {
        printf("Error: n must be > 0!\n");
        return;
    }

    double result = 0.0;

    for (int i = 1; i <= n; i++) {
        int exponent = i * i;
        result += pow(x, exponent);
    }

    printf("y = x^(1^2) + x^(2^2) + ... + x^(%d^2)\n", n);
    printf("y = x^1 + x^4 + ... + x^%d\n", n * n);
    printf("x = %.2f\n", x);
    printf("Result: %.6f\n", result);
}

void task24() {
    int n;

    printf("Enter natural number n: ");
    scanf_s("%d", &n);

    if (n <= 0) {
        printf("Error: n must be > 0!\n");
        return;
    }

    int result = 0;
    int multiplier = 1;
    int original_n = n;

    while (n > 0) {
        int digit = n % 10;

        if (digit != 0 && digit != 5) {
            result = digit * multiplier + result;
            multiplier *= 10;
        }

        n /= 10;
    }

    printf("Original number: %d\n", original_n);
    printf("After removing digits 0 and 5: %d\n", result);
}