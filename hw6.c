#include <stdio.h>
#include <math.h>

void task1();
void task2();

int main() {

	int choice;
	printf("Enter task number (1 or 2): ");
	scanf_s("%d", &choice);

	if (choice == 1) {
		task1();
	}
	else if (choice == 2) {
		task2();
	}
	else {
		printf("Invalid task number.\n");
	}
}

void task1() {

    int n;
    printf("Enter n: ");
    scanf_s("%d", &n);

    double a1 = 0.0;
    double a2 = 1.0;
    double sum = 0.0;

    for (int k = 1; k <= n; k++) {
        double current_term = 2 * k * a2;
        sum += current_term;

        double next_a = a2 + k * a1;
        a1 = a2;
        a2 = next_a;
    }

    printf("S = %f\n", sum);

    return 0;
}

void task2() {

    double x, eps;

    printf("Enter x (x >= 0): ");
    scanf_s("%lf", &x);
    if (x < 0) {
        printf("Error: x must be >= 0.\n");
        return 1;
    }

    printf("Enter epsilon (e > 0): ");
    scanf_s("%lf", &eps);
    if (eps <= 0) {
        printf("Error: epsilon must be > 0.\n");
        return 1;
    }

    double sum = 0.0;
    double term = x;
    int k = 0;
    int iterations = 0;

    while (fabs(term) >= eps) {
        sum += term;
        k++;

        term = pow(-1, k) * pow(x, 2 * k + 1);

        double denominator = 1.0;
        for (int i = 1; i <= k; i++) denominator *= i;
        for (int i = 1; i <= 2 * k + 1; i++) denominator *= i;

        term /= denominator;
        iterations++;
    }

    printf("Sum = %.10f\n", sum);
    printf("Iterations = %d\n", iterations);

    return 0;
 
}