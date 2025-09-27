#include <stdio.h>
#include <math.h>

void task1();
void task2();
void task3();
void task4();
void task5();
void task6();
void task7();

int main() {

	int choice;
	printf("Enter task number (1-7): ");
	scanf_s("%d", &choice);

	if (choice == 1) {
		task1();
	}
	else if (choice == 2) {
		task2();
	}
	else if (choice == 3) {
		task3();
	}
	else if (choice == 4) {
		task4();
	}
	else if (choice == 5) {
		task5();
	}
	else if (choice == 6) {
		task6();
	}
	else if (choice == 7) {
		task7();
	}
	else {
		printf("Invalid task number.\n");
	}
}

void task1() {
	int number;

	printf("Enter three-digit number: ");
	scanf_s("%d", &number);

	if (number < 100 || number > 999) {
		printf("Error: number must be three-digit (100-999)!\n");
		return;
	}

	// a)
	int hundreds = number / 100;
	int tens = (number / 10) % 10;
	int units = number % 10;

	printf("Digits:\n");
	printf("Hundreds: %d\n", hundreds);
	printf("Tens: %d\n", tens);
	printf("Units: %d\n", units);

	// b)
	int sum = hundreds + tens + units;
	printf("Sum of digits: %d\n", sum);

	// c)
	int reversed = units * 100 + tens * 10 + hundreds;
	printf("Reversed number: %d\n", reversed);
}

void task2() {

	int number;

	printf("Enter three-digit number: ");
	scanf_s("%d", &number);

	if (number < 100 || number > 999) {
		printf("Error: number must be three-digit (100-999)!\n");
		return;
	}

	int a = number / 100;
	int b = (number / 10) % 10;
	int c = number % 10;

	if (a == b || a == c || b == c) {
		printf("Digits are not all different!\n");
		return;
	}

	printf("All permutations of digits %d, %d, %d:\n", a, b, c);

	printf("%d%d%d\n", a, b, c);
	printf("%d%d%d\n", a, c, b);
	printf("%d%d%d\n", b, a, c);
	printf("%d%d%d\n", b, c, a);
	printf("%d%d%d\n", c, a, b);
	printf("%d%d%d\n", c, b, a);
}

void task3() {
	int a, b, c;

	printf("Enter 3 integers separated by commas: ");
	scanf_s("%d, %d, %d", &a, &b, &c);

	int product_a = a * b * c;
	printf("a) Product (|numbers| < 2^10): %d\n", product_a);

	long long product_b = (long long)a * b * c;
	printf("b) Product (|numbers| < 2^21): %lld\n", product_b);
}

void task4() {
	unsigned char a, b;

	printf("Enter first 8-bit number (0-255): ");
	scanf_s("%hhu", &a);
	printf("Enter second 8-bit number (0-255): ");
	scanf_s("%hhu", &b);

	unsigned short product = (unsigned short)a * (unsigned short)b;

	printf("8-bit numbers: %u, %u\n", a, b);
	printf("16-bit product: %u\n", product);
	printf("Max possible: 255 * 255 = %u\n", 255u * 255u);
}

void task5() {
	double a, b;

	printf("Enter first number: ");
	scanf_s("%lf", &a);
	printf("Enter second number: ");
	scanf_s("%lf", &b);

	if (a > b) {
		printf("Larger: %.2f\n", a);
		printf("Smaller: %.2f\n", b);
	}
	else if (a < b) {
		printf("Larger: %.2f\n", b);
		printf("Smaller: %.2f\n", a);
	}
	else {
		printf("Numbers are equal: %.2f\n", a);
	}
}

void task6() {
	double a, b, c;

	printf("Enter 3 numbers: ");
	scanf_s("%lf %lf %lf", &a, &b, &c);

	double abs_a = fabs(a);
	double abs_b = fabs(b);
	double abs_c = fabs(c);

	double max_abs = abs_a;
	if (abs_b > max_abs) max_abs = abs_b;
	if (abs_c > max_abs) max_abs = abs_c;

	double min_abs = abs_a;
	if (abs_b < min_abs) min_abs = abs_b;
	if (abs_c < min_abs) min_abs = abs_c;

	printf("Largest by absolute value: %.2f\n", max_abs);
	printf("Smallest by absolute value: %.2f\n", min_abs);
}

void task7() {
    double a, b, c;

    printf("Enter coefficients a, b, c: ");
    scanf_s("%lf %lf %lf", &a, &b, &c);

    // a)
    printf("\nQuadratic equation: %.2fx^2 + %.2fx + %.2f = 0\n", a, b, c);

    if (a == 0) {
        if (b == 0) {
            if (c == 0) printf("Infinite solutions (0 = 0)\n");
            else printf("No solutions (%f = 0)\n", c);
        }
        else {
            double x = -c / b;
            printf("Linear equation: x = %.2f\n", x);
        }
    }
    else {
        double D = b * b - 4 * a * c;

        if (D > 0) {
            double x1 = (-b + sqrt(D)) / (2 * a);
            double x2 = (-b - sqrt(D)) / (2 * a);
            printf("Two solutions: x1 = %.2f, x2 = %.2f\n", x1, x2);
        }
        else if (D == 0) {
            double x = -b / (2 * a);
            printf("One solution: x = %.2f\n", x);
        }
        else {
            printf("No real solutions (D < 0)\n");
        }
    }

    // b)
    printf("\nBiquadratic equation: %.2fx^4 + %.2fx^2 + %.2f = 0\n", a, b, c);

    if (a == 0) {
        printf("Not a biquadratic equation (a = 0)\n");
        return;
    }

    double D = b * b - 4 * a * c;

    if (D < 0) {
        printf("No real solutions\n");
    }
    else {
        double t1 = (-b + sqrt(D)) / (2 * a);
        double t2 = (-b - sqrt(D)) / (2 * a);

        int solutions = 0;

        if (t1 >= 0) {
            if (t1 == 0) {
                printf("x = 0\n");
                solutions++;
            }
            else {
                double x1 = sqrt(t1);
                double x2 = -sqrt(t1);
                printf("x = %.2f, x = %.2f\n", x1, x2);
                solutions += 2;
            }
        }

        if (t2 >= 0 && t2 != t1) {
            if (t2 == 0) {
                printf("x = 0\n");
                solutions++;
            }
            else {
                double x3 = sqrt(t2);
                double x4 = -sqrt(t2);
                printf("x = %.2f, x = %.2f\n", x3, x4);
                solutions += 2;
            }
        }

        if (solutions == 0) {
            printf("No real solutions\n");
        }
        else {
            printf("Total real solutions: %d\n", solutions);
        }
    }
}