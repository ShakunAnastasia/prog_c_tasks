#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int numerator;
    int denominator;
} Rational;

int gcd(int a, int b) {
    a = abs(a);
    b = abs(b);
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

Rational reduce_rational(Rational r) {
    if (r.denominator == 0) {
        printf("Error: Denominator cannot be zero!\n");
        return r;
    }

    int divisor = gcd(r.numerator, r.denominator);
    r.numerator /= divisor;
    r.denominator /= divisor;

    if (r.denominator < 0) {
        r.numerator = -r.numerator;
        r.denominator = -r.denominator;
    }

    return r;
}

Rational add_rational(Rational r1, Rational r2) {
    Rational result;
    result.numerator = r1.numerator * r2.denominator + r2.numerator * r1.denominator;
    result.denominator = r1.denominator * r2.denominator;
    return reduce_rational(result);
}

Rational multiply_rational(Rational r1, Rational r2) {
    Rational result;
    result.numerator = r1.numerator * r2.numerator;
    result.denominator = r1.denominator * r2.denominator;
    return reduce_rational(result);
}

int compare_rational(Rational r1, Rational r2) {
    long long num1 = (long long)r1.numerator * r2.denominator;
    long long num2 = (long long)r2.numerator * r1.denominator;

    if (num1 < num2) return -1;
    if (num1 > num2) return 1;
    return 0;
}

void input_rational(Rational* r) {
    while (1) {
        printf("Enter rational number (numerator denominator): ");
        if (scanf("%d %d", &r->numerator, &r->denominator) == 2) {
            if (r->denominator != 0) {
                break;
            }
        }
        printf("Error: Denominator cannot be zero!\n");
        while (getchar() != '\n');
    }
}

void print_rational(Rational r) {
    if (r.denominator == 1) {
        printf("%d", r.numerator);
    }
    else {
        printf("%d/%d", r.numerator, r.denominator);
    }
}

int main() {
    printf("Task 4.\n\n");

    Rational r1, r2;

    printf("Enter first rational number:\n");
    input_rational(&r1);

    printf("Enter second rational number:\n");
    input_rational(&r2);

    printf("\n");

    printf("First number: ");
    print_rational(r1);
    printf(" (reduced: ");
    print_rational(reduce_rational(r1));
    printf(")\n");

    printf("Second number: ");
    print_rational(r2);
    printf(" (reduced: ");
    print_rational(reduce_rational(r2));
    printf(")\n\n");

    Rational sum = add_rational(r1, r2);
    printf("Addition: ");
    print_rational(r1);
    printf(" + ");
    print_rational(r2);
    printf(" = ");
    print_rational(sum);
    printf("\n");

    Rational product = multiply_rational(r1, r2);
    printf("Multiplication: ");
    print_rational(r1);
    printf(" * ");
    print_rational(r2);
    printf(" = ");
    print_rational(product);
    printf("\n");

    int comparison = compare_rational(r1, r2);
    printf("Comparison: ");
    print_rational(r1);
    if (comparison < 0) {
        printf(" < ");
    }
    else if (comparison > 0) {
        printf(" > ");
    }
    else {
        printf(" = ");
    }
    print_rational(r2);
    printf("\n");

    return 0;
}