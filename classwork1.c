#include <stdio.h>
#include <math.h>
#define M_PI 3.14159265358979323846
#define M_E 2.71828182845904523536

void task1();
void task2();
void task3();
void task4();
void task5();
void task6();
void task7();
void task8();
void task9();

int main() {

	int choice;
	printf("Enter task number (1-9): ");
	scanf_s("%d", &choice);

	if (choice == 1) {
		task1();
	} else if (choice == 2) {
		task2();
	} else if (choice == 3) {
		task3();
	} else if (choice == 4) {
		task4();
	} else if (choice == 5) {
		task5();
	} else if (choice == 6) {
		task6();
	} else if (choice == 7) {
		task7();
	} else if (choice == 8) {
		task8();
	} else if (choice == 9) {
		task9();
	}
	else {
		printf("Invalid number.\n");
		return 0;
	}
	return 0;
}

void task1() {
	printf("%d \n", 2 + 31);
	printf("%d \n", 45 * 54 - 11);
	printf("%d \n", 15 / 4);
	printf("%.2f \n", 15.0 / 4);
	printf("%d \n", 67 % 5);
	printf("%.2f \n", (2 * 45.1 + 3.2) / 2);
}

void task2() {

	double a = 1e-4;
	double b = 24.33e5;
	double c = M_PI;
	double d = M_E;
	double e = sqrt(5.);
	double f = log(100.);

	printf("float:  %.2f %.2f %.2f %.2f %.2f %.2f\n",
		(float)a, (float)b, (float)c, (float)d, (float)e, (float)f);
	printf("double:      %.2f %.2f %.2f %.2f %.2f %.2f\n",
		a,b,c,d,e,f);
	printf("long double: %.2Lf %.2Lf %.2Lf %.2Lf %.2Lf %.2Lf\n",
		(long double)a, (long double)b, (long double)c,
		(long double)d, (long double)e, (long double)f);
}

void task3() {

	char a;

	printf("Enter a number: ");
	scanf_s(" %c", &a, 1);

	printf("- %c - %c - %c\n", a, a, a);
	printf("%c | %c | %c\n", a, a, a);
	printf("- %c - %c - %c\n", a, a, a);
}

void task4() {

	double G = 6.673e-11;
	double m1, m2, r, F;

	printf("Enter mass of first body: ");
	scanf_s("%lf", &m1);

	printf("Enter mass of second body: ");
	scanf_s("%lf", &m2);

	printf("Enter distance between bodies: ");
	scanf_s("%lf", &r);

	F = G * (m1 * m2) / (r * r);
	printf("F = %.2e N\n", F);
}


void task5() {

	double x;
	printf("Enter x: ");
	scanf_s("%lf", &x);

	double x2 = x * x;
	double x4 = x2 * x2;
	printf("a) x^4 = %.2f \n", x4);

	x2 = x * x;
	double x3 = x2 * x;
	double x6 = x3 * x3;
	printf("b) x^6 = %.2f \n", x6);

	x2 = x * x;
	x3 = x2 * x;
	double x9 = x3 * x3 * x3;
	printf("c) x^9 = %.2f \n", x9);

	x2 = x * x;
	x3 = x2 * x;
	x6 = x3 * x3;
	double x12 = x6 * x6; 
	double x15 = x12 * x3;
	printf("d) x^15 = %.2f \n", x15);

	x2 = x * x;
	x4 = x2 * x2;
	double x8 = x4 * x4;
	double x16 = x8 * x8;
	double x24 = x16 * x8;
	double x28 = x24 * x4;
	printf("e) x^28 = %.2f \n", x28);

	x2 = x * x;
	x4 = x2 * x2;
	x8 = x4 * x4;
	x16 = x8 * x8;
	double x32 = x16 * x16;
	double x64 = x32 * x32;
	printf("f) x^64 = %.2f \n", x64);

}


void task6() {

	double C, F;

	printf("Enter temperature in C: ");
	scanf_s("%lf", &C);

	F = (9.0 * C) / 5.0 + 32.0;

	printf("F = %g\n", F);

}

void task7() {

	double x;
	printf("Enter x: ");
	scanf_s("%lf", &x);

	double integer_part = floor(x);
	double fractional_part = x - integer_part;
	double ceil_value = ceil(x);
	double round_value = round(x);

	printf("Integer part: %.0f\n", integer_part);
	printf("Fractional part: %f\n", fractional_part);
	printf("Ceil: %.0f\n", ceil_value);
	printf("Round: %.0f\n", round_value);

}

void task8() {

	double a, b;

	printf("Enter first number: ");
	scanf_s("%lf", &a);
	printf("Enter second number: ");
	scanf_s("%lf", &b);

	double sum = a + b;
	double difference = a - b;
	double product = a * b;

	printf("Sum: %.2f\n", sum);
	printf("Difference: %.2f\n", difference);
	printf("Product: %.2f\n", product);

}

void task9() {

	double a, b, c;

	printf("Enter three numbers(with spaces between): ");
	scanf_s("%lf %lf %lf", &a, &b, &c);

	double arithmetic_mean = (a + b + c) / 3.0;
	double harmonic_mean = 3.0 / (1.0 / a + 1.0 / b + 1.0 / c);

	printf("Arithmetic mean (scientific): %.2e\n", arithmetic_mean);
	printf("Arithmetic mean (dec): %.2f\n", arithmetic_mean);
	printf("Harmonic mean (scientific): %.2e\n", harmonic_mean);
	printf("Harmonic mean (dec): %.2f\n", harmonic_mean);

}