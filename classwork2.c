#include <stdio.h.>
#include <math.h>

void task1();
void task2();
void task3();
void task4();
void task5();
void task6();

int main() {

	int choice;
	printf("Enter task number (1-6): ");
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
	else {
		printf("Invalid task number.\n");
	}

}

void task1() {
	double x;

	printf("Enter x: ");
	scanf_s("%lf", &x);

	double cos_x = cos(x);

	printf("cos(%.2f) = %.6f\n", x, cos_x);
}

void task2() {
	double a, b;

	printf("Enter leg a: ");
	scanf_s("%lf", &a);
	printf("Enter leg b: ");
	scanf_s("%lf", &b);

	if (a <= 0 || b <= 0) {
		printf("Error: a and b must be > 0 !\n");
		return;
	}

	double c = sqrt(a * a + b * b);

	printf("c = sqrt(%.2f^2 + %.2f^2) = %.6f\n", a, b, c);
}


void task3() {
	double a, b, c;

	printf("Enter side a: ");
	scanf_s("%lf", &a);
	printf("Enter side b: ");
	scanf_s("%lf", &b);
	printf("Enter side c: ");
	scanf_s("%lf", &c);

	if (a <= 0 || b <= 0 || c <= 0) {
		printf("Error: sides must be > 0!\n");
		return;
	}

	if (a + b <= c || a + c <= b || b + c <= a) {
		printf("Error: triangle inequality violated!\n");
		return;
	}

	double p = (a + b + c) / 2.0;
	double area = sqrt(p * (p - a) * (p - b) * (p - c));

	printf("S = %.6f\n", area);
}

void task4() {
	double x;

	printf("Enter x: ");
	scanf_s("%lf", &x);
	double y = (((x + 1) * x + 1) * x + 1) * x + 1;

	printf("y = x^4 + x^3 + x^2 + x + 1\n");
	printf("x = %.2f\n", x);
	printf("Result: %.6f\n", y);
}

void task5() {
	double x, y;

	printf("Enter x: ");
	scanf_s("%lf", &x);
	printf("Enter y: ");
	scanf_s("%lf", &y);
	double result = 100 * pow(x * x - y, 2) + pow(x - 1, 2);

	printf("Rosenbrock2d(x, y) = 100(x^2 - y)^2 + (x - 1)^2\n");
	printf("x = %.2f, y = %.2f\n", x, y);
	printf("Result: %.6f\n", result);
}

double distance(double x1, double y1, double x2, double y2) {
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

double triangle_area(double a, double b, double c) {
	double p = (a + b + c) / 2.0;
	return sqrt(p * (p - a) * (p - b) * (p - c));
}

void task6() {
	double ax, ay, bx, by, cx, cy;
	char temp;

	printf("Enter coordinates of point A (x y): ");
	scanf_s("%lf %lf", &ax, &ay);

	temp = getchar();

	printf("Enter coordinates of point B (x y): ");
	scanf_s("%lf %lf", &bx, &by);

	temp = getchar();

	printf("Enter coordinates of point C (x y): ");
	scanf_s("%lf %lf", &cx, &cy);

	double ab = distance(ax, ay, bx, by);
	double bc = distance(bx, by, cx, cy);
	double ca = distance(cx, cy, ax, ay);

	if (ab + bc <= ca || ab + ca <= bc || bc + ca <= ab) {
		printf("Error: points do not form a triangle!\n");
		return;
	}

	double area = triangle_area(ab, bc, ca);

	printf("\nTriangle vertices:\n");
	printf("A(%.2f, %.2f)\n", ax, ay);
	printf("B(%.2f, %.2f)\n", bx, by);
	printf("C(%.2f, %.2f)\n", cx, cy);
	printf("Side lengths: AB = %.2f, BC = %.2f, CA = %.2f\n", ab, bc, ca);
	printf("Area: %.6f\n", area);
}