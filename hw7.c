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
		printf("Invalid task nubmer.\n");
	}
	
}

void task1() {

    int n;

    printf("Enter natural number n: ");
    if (scanf_s("%d", &n) != 1) {
        printf("Error!\n");
        return;
    }

    if (n <= 0) {
        printf("Error: n must be > 0!\n");
        return;
    }

    int arr[100];

    printf("Enter %d natural numbers:\n", n);
    for (int i = 0; i < n; i++) {
        printf("a%d: ", i + 1);
        if (scanf_s("%d", &arr[i]) != 1) {
            printf("Error!\n");
            return;
        }
        if (arr[i] <= 0) {
            printf("Error: numbers must be > 0!\n");
            return;
        }
    }

    int k = n / 2;
    int perfect_square_count = 0;

    printf("\nChecking products for perfect squares:\n");
    for (int i = 0; i < k; i++) {
        int product = arr[i] * arr[n - 1 - i];
        int root = (int)sqrt(product);

        if (root * root == product) {
            printf("a%d * a%d = %d * %d = %d = %d^2 (perfect square)\n",
                i + 1, n - i, arr[i], arr[n - 1 - i], product, root);
            perfect_square_count++;
        }
        else {
            printf("a%d * a%d = %d * %d = %d (not perfect square)\n",
                i + 1, n - i, arr[i], arr[n - 1 - i], product);
        }
    }

    printf("\nTotal perfect squares: %d\n", perfect_square_count);
}


void task2() {
    int N;

    printf("Enter array size N: ");
    if (scanf_s("%d", &N) != 1) {
        printf("Error!\n");
        return;
    }

    if (N <= 0) {
        printf("Error: array size must be > 0!\n");
        return;
    }

    int A[100];

    printf("Enter %d integers:\n", N);
    for (int i = 0; i < N; i++) {
        printf("A[%d]: ", i);
        if (scanf_s("%d", &A[i]) != 1) {
            printf("Error!\n");
            return;
        }
    }

    int min = A[0];
    int max = A[0];

    for (int i = 1; i < N; i++) {
        if (A[i] < min) {
            min = A[i];
        }
        if (A[i] > max) {
            max = A[i];
        }
    }

    double average = (min + max) / 2.0;

    int closest_element = A[0];
    double min_difference = fabs(A[0] - average);

    for (int i = 1; i < N; i++) {
        double difference = fabs(A[i] - average);
        if (difference < min_difference) {
            min_difference = difference;
            closest_element = A[i];
        }
    }

    printf("\nArray: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");

    printf("Min element: %d\n", min);
    printf("Max element: %d\n", max);
    printf("Average of min and max: %.2f\n", average);
    printf("Closest element to average: %d (difference: %.2f)\n", closest_element, min_difference);
}