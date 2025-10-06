#include <stdio.h>
#include <math.h>
#define N 10
#define ms 20

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
    double numbers[5];

    printf("Enter 5 numbers:\n");
    for (int i = 0; i < 5; i++) {
        if (scanf_s("%lf", &numbers[i]) != 1) {
            printf("Error!\n");
            return;
        }
    }

    double reference;
    printf("Enter reference number: ");
    if (scanf_s("%lf", &reference) != 1) {
        printf("Error!\n");
        return;
    }

    int count = 0;
    for (int i = 0; i < 5; i++) {
        if (numbers[i] < reference) {
            count++;
        }
    }

    printf("Count of numbers less than %.2f: %d\n", reference, count);
}


void task2() {
    int arr[] = { 5, 112, 4, 3 };
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("Reversed array: ");
    for (int i = size - 1; i >= 0; i--) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}


void task3() {
    double arr[N];
    const double euler = exp(1.0);

    printf("Enter %d double numbers:\n", N);
    for (int i = 0; i < N; i++) {
        printf("Element %d: ", i + 1);
        if (scanf_s("%lf", &arr[i]) != 1) {
            printf("Error!\n");
            return;
        }
    }

    double sum = 0.0;
    int count = 0;

    for (int i = 0; i < N; i++) {
        if (arr[i] > euler) {
            sum += arr[i];
            count++;
        }
    }

    printf("Euler's number e = %.15f\n", euler);
    printf("Sum of elements greater than e: %.6f\n", sum);
    printf("Number of elements greater than e: %d\n", count);
}

void task4() {
    int arr[5];

    printf("Enter 5 integer numbers:\n");
    for (int i = 0; i < 5; i++) {
        printf("Element %d: ", i + 1);
        if (scanf_s("%d", &arr[i]) != 1) {
            printf("Error!\n");
            return;
        }
    }

    int max = arr[0];
    for (int i = 1; i < 5; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    printf("Array elements: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("Maximum value: %d\n", max);
}

void task5() {
    int arr[50];
    int count = 0;
    int n;

    printf("Enter natural numbers (max 50, 0 to stop):\n");

    for (int i = 0; i < 50; i++) {
        printf("Element %d: ", i + 1);
        if (scanf_s("%d", &arr[i]) != 1) {
            printf("Error!\n");
            return;
        }

        if (arr[i] < 0) {
            printf("Error: only natural numbers (positive integers) allowed\n");
            return;
        }

        if (arr[i] == 0) {
            n = i;
            break;
        }

        count++;
        n = count;

        if (i == 49) {
            n = 50;
            printf("Maximum capacity reached (50 elements)\n");
        }
    }

    int even_count = 0;
    int odd_count = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0) {
            even_count++;
        }
        else {
            odd_count++;
        }
    }

    printf("\nArray elements (%d numbers): ", n);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("Even numbers count: %d\n", even_count);
    printf("Odd numbers count: %d\n", odd_count);
}


void inputVector(double vector[], int n) {
    printf("Enter %d vector elements:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Element %d: ", i + 1);
        if (scanf_s("%lf", &vector[i]) != 1) {
            printf("Error!\n");
            return;
        }
    }
}

void printVector(double vector[], int n) {
    printf("(");
    for (int i = 0; i < n; i++) {
        printf("%.2f", vector[i]);
        if (i < n - 1) {
            printf(", ");
        }
    }
    printf(")\n");
}

void vectorSum(double vec1[], double vec2[], double result[], int n) {
    for (int i = 0; i < n; i++) {
        result[i] = vec1[i] + vec2[i];
    }
}

double dotProduct(double vec1[], double vec2[], int n) {
    double result = 0.0;
    for (int i = 0; i < n; i++) {
        result += vec1[i] * vec2[i];
    }
    return result;
}

void task6() {
    int n;
	double vec1[ms], vec2[ms],sum[ms];

    printf("Enter vector dimension (n < 20): ");
    if (scanf_s("%d", &n) != 1) {
        printf("Error!\n");
        return;
    }

    if (n <= 0 || n >= 20) {
        printf("Error: dimension must be between 1 and 19\n");
        return;
    }

    printf("\nFirst vector\n");
    inputVector(vec1, n);

    printf("\nSecond vector \n");
    inputVector(vec2, n);

    printf("\nResults \n");
    printf("First vector: ");
    printVector(vec1, n);

    printf("Second vector: ");
    printVector(vec2, n);

    vectorSum(vec1, vec2, sum, n);
    printf("Vector sum: ");
    printVector(sum, n);

    double dot = dotProduct(vec1, vec2, n);
    printf("Dot product: %.2f\n", dot);
}