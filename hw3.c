#include <stdio.h>
#include <float.h>
#include <math.h>
#define pi 3.14159265358979323846

void task1();
void task2();

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

double circle_segment_area(double y, double r) {
    if (y >= r) return 0;
    if (y <= -r) return pi * r * r;
    return r * r * acos(y / r) - y * sqrt(r * r - y * y);
}

void task1() {
    double r, a, b, e;

    printf("Enter r: ");
    scanf_s("%lf", &r);

    printf("Enter a: ");
    scanf_s("%lf", &a);

    printf("Enter b: ");
    scanf_s("%lf", &b);

    printf("Enter e: ");
    scanf_s("%lf", &e);

    if (r <= 0 || e <= 0) {
        printf("Error! r and e must be > 0.\n");
        return;
    }

    double y_low = fmax(-r, b);
    double y_high = fmin(r, b + e);

    double area;
    if (y_high <= y_low) {
        area = 0.0;
    }
    else {
        area = circle_segment_area(y_low, r) - circle_segment_area(y_high, r);
    }

    printf("\nResults:\n");
    printf("Circle: x^2 + y^2 = %.2f²\n", r);
    printf("Horizontal strip: y ∈ [%.2f, %.2f]\n", b, b + e);
    printf("Intersection area: %.6f\n", area);
}

double step(double x) {
    if (x >= 0) return 1.0;
    else return 0.0;
}

double step_derivative(double x) {
    double small = 0.0000001;

    if (fabs(x) < small) {
        return 1000000000.0;
    }
    else {
        return 0.0;
    }
}

void task2() {
    printf("Testing step function and its derivative:\n\n");

    double values[] = { -2.0, -1.0, -0.5, -0.1, 0.0, 0.1, 0.5, 1.0, 2.0 };

    for (int i = 0; i < 9; i++) {
        double x = values[i];
        double y = step(x);
        double dy = step_derivative(x);

        printf("x = %5.1f: step(x) = %.1f", x, y);

        if (dy > 999999999.0) {
            printf(", derivative = inf\n");
        }
        else {
            printf(", derivative = %.1f\n", dy);
        }
    }
}
