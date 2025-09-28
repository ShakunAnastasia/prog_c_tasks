#include <stdio.h>
#include <math.h>

void task1();
void task2();
void task3();
void task4();
void task5();
void task6();
void task7();
void task8();

int main() {

	int choice;
	printf("Enter task number (1-8): ");
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
	else {
		printf("Invalid task number.\n");
	}

}

void task1() {

	double a;

	printf("Enter number a: ");
	scanf_s("%lf", &a);

	// à)
	double sum_a = 0.0;
	int n_a = 0;

	do {
		n_a++;
		sum_a += 1.0 / n_a;
	} while (sum_a <= a);

	printf("First number > %.2f: 1", a);
	for (int i = 2; i <= n_a; i++) {
		printf(" + 1/%d", i);
	}
	printf(" = %.6f (n = %d)\n", sum_a, n_a);

	// b)
	double sum_b = 0.0;
	int n_b = 0;

	while (sum_b <= a) {
		n_b++;
		sum_b += 1.0 / n_b;
	}

	printf("Smallest n > 0: n = %d (sum = %.6f)\n", n_b, sum_b);
}

void task2() {
    // à)
    int n;
    printf("a) Enter n to compute F_n: ");
    scanf_s("%d", &n);

    long long fib_prev = 0, fib_curr = 1;

    if (n == 0) {
        printf("F_0 = 0\n");
    }
    else if (n == 1) {
        printf("F_1 = 1\n");
    }
    else {
        for (int i = 2; i <= n; i++) {
            long long fib_next = fib_prev + fib_curr;
            fib_prev = fib_curr;
            fib_curr = fib_next;
        }
        printf("F_%d = %lld\n", n, fib_curr);
    }

    // b)
    long long a;
    printf("\nb) Enter a to find largest Fibonacci <= a: ");
    scanf_s("%lld", &a);

    fib_prev = 0;
    fib_curr = 1;
    int index = 0;

    while (fib_curr <= a) {
        long long fib_next = fib_prev + fib_curr;
        fib_prev = fib_curr;
        fib_curr = fib_next;
        index++;
    }

    printf("Largest Fibonacci <= %lld: F_%d = %lld\n", a, index, fib_prev);

    // c)
    printf("\nc) Enter a to find smallest Fibonacci > a: ");
    scanf_s("%lld", &a);

    fib_prev = 0;
    fib_curr = 1;
    index = 0;

    while (fib_curr <= a) {
        long long fib_next = fib_prev + fib_curr;
        fib_prev = fib_curr;
        fib_curr = fib_next;
        index++;
    }

    printf("Smallest Fibonacci > %lld: F_%d = %lld\n", a, index + 1, fib_curr);

    // d)
    printf("\nd) Sum of Fibonacci numbers <= 1000:\n");

    fib_prev = 0;
    fib_curr = 1;
    long long sum = 0;

    while (fib_curr <= 1000) {
        sum += fib_curr;
        long long fib_next = fib_prev + fib_curr;
        fib_prev = fib_curr;
        fib_curr = fib_next;
    }

    printf("Sum = %lld\n", sum);
}

void task3() {
    int n;

    printf("Enter natural number n: ");
    scanf_s("%d", &n);

    if (n <= 0 || n >= 1000) {
        printf("Error: n must be in range 1-999\n");
        return;
    }

    // à)
    int current = n;
    int steps = 0;

    printf("Sequence for n = %d:\n", n);
    printf("%d", current);

    while (current != 1) {
        if (current % 2 == 0) {
            current = current / 2;
        }
        else {
            current = 3 * current + 1;
        }
        printf(" -> %d", current);
        steps++;
    }
    printf("\nSteps to reach 1: %d\n", steps);

    // b)
    printf("\nFinding number with maximum steps for n < 1000:\n");

    int max_steps = 0;
    int number_with_max_steps = 1;

    for (int i = 1; i < 1000; i++) {
        current = i;
        steps = 0;

        while (current != 1) {
            if (current % 2 == 0) {
                current = current / 2;
            }
            else {
                current = 3 * current + 1;
            }
            steps++;
        }

        if (steps > max_steps) {
            max_steps = steps;
            number_with_max_steps = i;
        }
    }

    printf("Number with maximum steps: %d\n", number_with_max_steps);
    printf("Maximum steps: %d\n", max_steps);

    printf("\nSequence for n = %d:\n", number_with_max_steps);
    current = number_with_max_steps;
    printf("%d", current);

    while (current != 1) {
        if (current % 2 == 0) {
            current = current / 2;
        }
        else {
            current = 3 * current + 1;
        }
        printf(" -> %d", current);
    }
    printf("\n");
}


void task4() {
    int n;

    printf("Enter n: ");
    scanf_s("%d", &n);

    if (n <= 0) {
        printf("Error: n must be > 0!\n");
        return;
    }

    // à)
    double product_a = 1.0;
    double factorial = 1.0;

    printf("a) Result: %d:\n", n);
    printf("P_0 = 1.0\n");

    for (int i = 1; i <= n; i++) {
        factorial *= i;
        double factor = 1.0 + 1.0 / factorial;
        product_a *= factor;
        printf("P_%d = P_%d * (1 + 1/%d!) = %.6f\n", i, i - 1, i, product_a);
    }

    printf("Final result: %.10f\n\n", product_a);

    // b)
    double product_b = 1.0;
    double power_of_2 = 1.0;

    printf("b) Result: %d:\n", n);
    printf("P_0 = 1.0\n");

    for (int i = 1; i <= n; i++) {
        power_of_2 *= 2.0;
        double sign = (i % 2 == 1) ? 1.0 : -1.0;
        double factor = 1.0 + (sign * i * i) / power_of_2;
        product_b *= factor;
        printf("Result = %.6f\n",
            i, i - 1, sign, i, power_of_2, product_b);
    }

    printf("Final result: %.10f\n", product_b);
}

void task5() {
    int n;

    printf("Enter n (n >= 3): ");
    scanf_s("%d", &n);

    if (n < 3) {
        printf("Error: n must be >= 3!\n");
        return;
    }

    int x_prev3 = -99;
    int x_prev2 = -99; 
    int x_prev1 = -99;
    int x_current;

    printf("Sequence: x0 = %d, x1 = %d, x2 = %d\n", x_prev3, x_prev2, x_prev1);

    for (int i = 3; i <= n; i++) {
        x_current = x_prev1 + x_prev3 + 100;

        printf("x_%d = x_%d + x_%d + 100 = %d + %d + 100 = %d\n",
            i, i - 1, i - 3, x_prev1, x_prev3, x_current);

        x_prev3 = x_prev2;
        x_prev2 = x_prev1;
        x_prev1 = x_current;
    }

    printf("\nResult: x_%d = %d\n", n, x_current);
}

void task6() {
    int n;
    double b;

    printf("Enter n: ");
    scanf_s("%d", &n);

    if (n <= 0) {
        printf("Error: n must be > 0!\n");
        return;
    }

    // à)
    printf("a) Enter b: ");
    scanf_s("%lf", &b);

    double result_a = b;
    for (int i = 1; i < n; i++) {
        result_a = b + 1.0 / result_a;
    }
    printf("b_%d = %.10f\n\n", n, result_a);

    // b)
    double result_b = 4 * n + 2;

    for (int k = 1; k <= n; k++) {
        result_b = 4 * (n - k) + 2 + 1.0 / result_b;
    }
    printf("b) lambda_%d = %.10f\n\n", n, result_b);

    // c)
    double result_c = 2.0;

    for (int i = 1; i < 2 * n; i++) {
        if (i % 2 == 1) {
            result_c = 1.0 + 1.0 / result_c;
        }
        else {
            result_c = 2.0 + 1.0 / result_c;
        }
    }
    printf("c) x_%d = %.10f\n", 2 * n, result_c);
}

void task7() {
    int n;

    printf("Enter n (n >= 2): ");
    scanf_s("%d", &n);

    if (n < 2) {
        printf("Error: n must be >= 2!\n");
        return;
    }

    double a_prev2 = 0.0;
    double a_prev1 = 1.0;
    double b_prev2 = 1.0;  
    double b_prev1 = 0.0;

    double sum = 0.0;

    printf("k=1: a1=%.1f, b1=%.1f, term=2^1/(%.1f+%.1f)=%.6f\n",
        a_prev2, b_prev2, a_prev2, b_prev2, pow(2, 1) / (a_prev2 + b_prev2));
    sum += pow(2, 1) / (a_prev2 + b_prev2);

    printf("k=2: a2=%.1f, b2=%.1f, term=2^2/(%.1f+%.1f)=%.6f\n",
        a_prev1, b_prev1, a_prev1, b_prev1, pow(2, 2) / (a_prev1 + b_prev1));
    sum += pow(2, 2) / (a_prev1 + b_prev1);

    for (int k = 3; k <= n; k++) {
        double a_current = a_prev1 / k + a_prev2 * b_prev1;
        double b_current = b_prev1 + a_prev1;
        double term = pow(2, k) / (a_current + b_current);

        printf("k=%d: a_%d=%.6f, b_%d=%.6f, term=2^%d/(%.6f+%.6f)=%.6f\n",
            k, k, a_current, k, b_current, k, a_current, b_current, term);

        sum += term;

        a_prev2 = a_prev1;
        a_prev1 = a_current;
        b_prev2 = b_prev1;
        b_prev1 = b_current;
    }

    printf("\nFinal sum S_%d = %.10f\n", n, sum);
}

void task8() {
    double epsilon, x;

    printf("Enter precision e: ");
    scanf_s("%lf", &epsilon);

    printf("Enter x value: ");
    scanf_s("%lf", &x);

    // a)
    double exp_taylor = 1.0;
    double term = 1.0;
    int n = 1;

    while (fabs(term) >= epsilon) {
        term *= x / n;
        exp_taylor += term;
        n++;
    }

    double exact_exp = exp(x);
    printf("\na) e^x calculation:\n");
    printf("Taylor series result: %.10f\n", exp_taylor);
    printf("Exact math function:  %.10f\n", exact_exp);
    printf("Difference: %.10f\n", fabs(exp_taylor - exact_exp));

    // b)
    double integral_taylor = x;
    double term_integral = x;
    int k = 1;
    n = 1;

    do {
        term_integral = term_integral * (-x * x) / (2 * n + 1);
        term_integral = term_integral * (2 * n - 1) / (2 * n - 1);

        term_integral = pow(-1, n) * pow(x, 2 * n + 1) / ((2 * n + 1) * tgamma(n + 1));

        integral_taylor += term_integral;
        n++;
    } while (fabs(term_integral) >= epsilon);

    double exact_integral = 0.0;
    int steps = 10000;
    double dx = x / steps;
    double sum = 0.0;

    for (int i = 0; i < steps; i++) {
        double x_val = i * dx;
        sum += exp(-x_val * x_val) * dx;
    }
    exact_integral = sum;

    printf("\ná) Result:  \n");
    printf("Taylor series result: %.10f\n", integral_taylor);
    printf("Numerical integration: %.10f\n", exact_integral);
    printf("Difference: %.10f\n", fabs(integral_taylor - exact_integral));
}