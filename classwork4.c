#include <stdio.h>
#include <math.h>
#include <float.h>

void task1();
void task2();
void task3();
void task4();
void task5();
void task6();
void task7();
void task8();
void task9();
void task10();
void task11();
void task12();

int main() {

	int choice;
	printf("Enter task number (1-12): ");
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
	else if (choice == 8) {
		task8();
	}
	else if (choice == 9) {
		task9();
	}
	else if (choice == 10) {
		task10();
	}
	else if (choice == 11) {
		task11();
	}
	else if (choice == 12) {
		task12();
	}
	else {
		printf("Invalid number.\n");
		return 0;
	}
	return 0;
}

void task1() {

	double x;
	int n;

	printf("Enter x: ");
	scanf_s("%lf", &x);
	printf("Enter n: ");
	scanf_s("%d", &n);

	double result = x;

	for (int i = 0; i < n; i++) {
		result = sin(result);
	}

	printf("sin(sin(...sin(x)...)) (%d times) = %.6f\n", n, result);
}

void task2() {

	int n;

	printf("Enter natural number n: ");
	scanf_s("%d", &n);

	if (n < 0) {
		printf("Error: n must be >= 0!\n");
		return;
	}

	printf("Cycle with increment:\n");
	printf("%d! = ", n);

	if (n == 0) {
		printf("1");
	}
	else {
		for (int i = 1; i <= n; i++) {
			printf("%d", i);
			if (i < n) {
				printf("*");
			}
		}
	}
	printf("\n");

	printf("Cycle with decrement:\n");
	printf("%d! = ", n);

	if (n == 0) {
		printf("1");
	}
	else {
		for (int i = n; i >= 1; i--) {
			printf("%d", i);
			if (i > 1) {
				printf("*");
			}
		}
	}
	printf("\n");
}

void task3() {

	// a) 
	int n_a = 3;
	double x_a = 2.0;
	double result_a = 0.0;

	for (int i = n_a; i >= 0; i--) {
		result_a += pow(x_a, i);
	}

	printf("y = x^%d + x^%d + ... + x + 1, x = %.0f\n", n_a, n_a - 1, x_a);
	printf("Result of a): %.0f\n", result_a);

	// b) 
	int n_b = 4;
	double x_b = 1.0;
	double y_b = 2.0;
	double result_b = 0.0;

	for (int i = n_b; i >= 0; i--) {
		if (i == 0) {
			result_b += 1.0;
		}
		else {
			double exponent = pow(2, i);
			result_b += pow(x_b, exponent) * pow(y_b, i);
		}
	}

	printf("y = x^(2^%d)*y^%d + ... + x^2*y + 1, x = %.0f, y = %.0f\n", n_b, n_b, x_b, y_b);
	printf("Result of b): %.0f\n", result_b);
}

void task4() {

	int n;
	double x;

	printf("Enter n: ");
	scanf_s("%d", &n);

	if (n <= 0) {
		printf("Error: n must be > 0!\n");
		return;
	}

	printf("Enter x: ");
	scanf_s("%lf", &x);

	double result = 0.0;

	for (int i = 1; i <= n; i++) {
		result += i * pow(x, i);
	}

	printf("x + 2*x^2 + 3*x^3 + ... + %d*x^%d\n", n, n);
	printf("x = %.2f\n", x);
	printf("Result: %.2f\n", result);
}

void task5() {

	int n;

	printf("Enter natural number n: ");
	scanf_s("%d", &n);

	if (n < 0) {
		printf("Error: n must be natural number!\n");
		return;
	}

	if (n == 0 || n == 1) {
		printf("%d!! = 1\n", n);
		return;
	}

	long long double_factorial = 1;

	if (n % 2 == 0) {
		for (int i = 2; i <= n; i += 2) {
			double_factorial *= i;
		}
		printf("%d!! = ", n);
		for (int i = 2; i <= n; i += 2) {
			printf("%d", i);
			if (i < n) {
				printf(" * ");
			}
		}
	}
	else {
		for (int i = 1; i <= n; i += 2) {
			double_factorial *= i;
		}
		printf("%d!! = ", n);
		for (int i = 1; i <= n; i += 2) {
			printf("%d", i);
			if (i < n) {
				printf(" * ");
			}
		}
	}

	printf(" = %lld\n", double_factorial);
}

void task6() {

	int n;

	printf("Enter n: ");
	scanf_s("%d", &n);

	if (n <= 0) {
		printf("Error: n must be > 0!\n");
		return;
	}

	// a)
	double result_a = sqrt(2.0);
	for (int i = 2; i <= n; i++) {
		result_a = sqrt(2.0 + result_a);
	}

	printf("a) sqrt(2 + sqrt(2 + ... + sqrt(2))) (%d roots) = %.6f\n", n, result_a);

	// b)
	double result_b = sqrt(3.0 * n);
	for (int i = n - 1; i >= 1; i--) {
		result_b = sqrt(3.0 * i + result_b);
	}

	printf("b) sqrt(3 + sqrt(6 + ... + sqrt(3n))) (%d roots) = %.6f\n", n, result_b);
}

void task7() {

	double x;
	int n;

	printf("Enter x: ");
	scanf_s("%lf", &x);
	printf("Enter n: ");
	scanf_s("%d", &n);

	if (n < 0) {
		printf("Error: n must be >= 0!\n");
		return;
	}

	double result = 1.0;

	for (int i = 1; i <= n; i++) {
		result += pow(x, i);
	}

	printf("y = 1 + x + x^2 + ... + x^%d\n", n);
	printf("x = %.2f\n", x);
	printf("Result: %.6f\n", result);
}	

void task8() {

	int m;

	printf("Enter m (m > 1): ");
	scanf_s("%d", &m);

	if (m <= 1) {
		printf("Error: m must be > 1!\n");
		return;
	}

	int k = 0;
	int power = 1;

	while (power * 4 < m) {
		k++;
		power *= 4;
	}

	printf("Largest k where 4^k < %d: k = %d\n", m, k);
	printf("4^%d = %d < %d\n", k, power, m);
	printf("4^%d = %d >= %d\n", k + 1, power * 4, m);

}

void task9() {

	int n;

	printf("Enter natural number n: ");
	scanf_s("%d", &n);

	if (n < 0) {
		printf("Error: n must be >= 0!\n");
		return;
	}

	int k = 0;
	int power = 1;

	while (power <= n) {
		k++;
		power *= 2;
	}

	printf("Smallest k where 2^k > %d: k = %d\n", n, k);
	printf("2^%d = %d > %d\n", k, power, n);
	printf("2^%d = %d <= %d\n", k - 1, power / 2, n);
}

void task10() {

	float a = 1.0f;

	while (1.0f + a / 2.0f != 1.0f) {
		a /= 2.0f;
	}

	printf("Machine eps for float: %e\n", a);
	printf("1 + %e = 1 + %.20f\n", a, a);
	printf("1 + a == 1: %s\n", (1.0f + a == 1.0f) ? "true" : "false");

	printf("From float.h: %e\n", FLT_EPSILON);
}

void task11() {

	double number;
	int count = 0;
	double sum = 0.0;
	double product = 1.0;

	printf("Enter sequence of non-zero numbers (0 to stop):\n");

	while (1) {
		printf("a[%d] = ", count);
		scanf_s("%lf", &number);

		if (number == 0.0) {
			break;
		}

		sum += number;
		product *= number;
		count++;
	}

	if (count == 0) {
		printf("No numbers entered!\n");
		return;
	}

	double arithmetic_mean = sum / count;
	double geometric_mean = pow(product, 1.0 / count);

	printf("\nResults:\n");
	printf("Numbers entered: %d\n", count);
	printf("Sum: %.6f\n", sum);
	printf("Arithmetic mean: %.6f\n", arithmetic_mean);
	printf("Geometric mean: %.6f\n", geometric_mean);
}

void task12() {

	int n;

	printf("Enter natural number n (n < 25): ");
	scanf_s("%d", &n);

	if (n < 0 || n >= 25) {
		printf("Error: n must be in range 0 <= n < 25\n");
		return;
	}

	double sum = 0.0;
	double term = 1.0; 

	for (int i = 0; i <= n; i++) {
		if (i > 0) {
			term /= i;
		}

		if (i % 2 == 0) {
			sum += term;
		}
		else {
			sum -= term;
		}
	}


	double factorial = 1.0;
	for (int i = 1; i <= n; i++) {
		factorial *= i;
	}

	double subfactorial = factorial * sum;

	printf("!%d = %.0f\n", n, subfactorial);
	printf("Formula: %d! * (1 - 1/1! + 1/2! - ... + (-1)^%d/%d!)\n", n, n, n);
	printf("Result: %.0f * %.10f = %.0f\n", factorial, sum, subfactorial);
}