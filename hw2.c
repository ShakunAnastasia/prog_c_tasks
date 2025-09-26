#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

double arctg(double x) {
    return atan(x); 
}

double arctg_derivative(double x) {
    return 1.0 / (1.0 + x * x);
}

int main() {
    int choice;

    printf("Choose task (1 or 2): ");
    scanf_s("%d", &choice);

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
    double r, R, area;

    printf("Enter r: ");
    scanf_s("%lf", &r);

    printf("Enter R: ");
    scanf_s("%lf", &R);

    if (R <= r) {
        printf("Error! R must be greater than r.\n");
        return;
    }

    if (r <= 0 || R <= 0) {
        printf("Error! R and r must be > 0.\n");
        return;
    }

    area = 2 * PI * PI * R * r * r;

    printf("Area = %.2f\n", area);
}

void task2() {
    double x;

    printf("Enter x: ");
    scanf_s("%lf", &x);

    printf("f(x) = arctg(x) = %.6f\n", arctg(x));
    printf("f'(x) = 1/(1+x^2) = %.6f\n", arctg_derivative(x));
}
