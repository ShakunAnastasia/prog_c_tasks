#include <stdio.h>
#include <math.h>
#define MAX_SIZE 10

void task1();
void task2();
void task3();
void task4();
void task5();
void task6();
void task7();

int main() {

	int choice;
	printf("Enter task number (1-7): ");
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
	else {
		printf("Invalid task number.\n");
	}

}

void task1() {
    int matrix[3][3] = { {1, 2, 3},
                       {4, 5, 6},
                       {7, 8, 9} };
    int N, M;
    int found = 0;

    printf("Initial matrix:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    printf("Enter natural number N: ");
    if (scanf_s("%d", &N) != 1 || N <= 0) {
        printf("Error: N must be a natural number.\n");
        return;
    }

    printf("Enter natural number M: ");
    if (scanf_s("%d", &M) != 1 || M <= 0) {
        printf("Error: M must be a natural number.\n");
        return;
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (matrix[i][j] == M) {
                matrix[i][j] = N;
                found = 1;
                printf("Replaced element at position [%d][%d] (%d -> %d)\n", i, j, M, N);
            }
        }
    }

    if (!found) {
        printf("Element %d not found in matrix.\n", M);
    }

    printf("\nResult matrix:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void task2() {
    float matrix[3][3] = { {1.0, 2.3, 0},
                         {4, 5, 6},
                         {7, 8, 9} };
    int i, j;
    float a;

    printf("Initial matrix:\n");
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            printf("%.1f ", matrix[row][col]);
        }
        printf("\n");
    }

    printf("Enter natural number i (0-2): ");
    if (scanf_s("%d", &i) != 1 || i < 0 || i > 2) {
        printf("Error: i must be a natural number between 0 and 2.\n");
        return;
    }

    printf("Enter natural number j (0-2): ");
    if (scanf_s("%d", &j) != 1 || j < 0 || j > 2) {
        printf("Error: j must be a natural number between 0 and 2.\n");
        return;
    }

    printf("Enter number a: ");
    if (scanf_s("%f", &a) != 1) {
        printf("Error: invalid input for a.\n");
        return;
    }

    printf("Replaced element at position [%d][%d] (%.1f -> %.1f)\n",
        i, j, matrix[i][j], a);
    matrix[i][j] = a;

    printf("\nResult matrix:\n");
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            printf("%.1f ", matrix[row][col]);
        }
        printf("\n");
    }
}

void task3() {
    int matrix[20][20];
    int m, n;

    printf("Enter number of rows m (m < 20): ");
    if (scanf_s("%d", &m) != 1 || m <= 0 || m >= 20) {
        printf("Error: m must be a natural number less than 20.\n");
        return;
    }

    printf("Enter number of columns n (n < 20): ");
    if (scanf_s("%d", &n) != 1 || n <= 0 || n >= 20) {
        printf("Error: n must be a natural number less than 20.\n");
        return;
    }

    printf("Enter matrix elements (%d x %d):\n", m, n);
    for (int i = 0; i < m; i++) {
        printf("Row %d: ", i);
        for (int j = 0; j < n; j++) {
            if (scanf_s("%d", &matrix[i][j]) != 1) {
                printf("Error: invalid input for element [%d][%d].\n", i, j);
                return;
            }
        }
    }

    printf("\nEntered matrix (%d x %d):\n", m, n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void task4() {
    int matrix[25][25];
    int m, n;

    printf("Enter number of rows m (m < 25): ");
    if (scanf_s("%d", &m) != 1 || m <= 0 || m >= 25) {
        printf("Error: m must be a natural number between 1 and 24.\n");
        return;
    }

    printf("Enter number of columns n (n < 25): ");
    if (scanf_s("%d", &n) != 1 || n <= 0 || n >= 25) {
        printf("Error: n must be a natural number between 1 and 24.\n");
        return;
    }

    printf("Enter matrix elements (%d x %d):\n", m, n);
    for (int i = 0; i < m; i++) {
        printf("Row %d: ", i);
        for (int j = 0; j < n; j++) {
            if (scanf_s("%d", &matrix[i][j]) != 1) {
                printf("Error: invalid input for element [%d][%d].\n", i, j);
                return;
            }
        }
    }

    printf("\nEntered matrix (%d x %d):\n", m, n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void task5() {
    int matrix[10][10];
    int n;

    printf("Enter size of square matrix n (n <= 10): ");
    if (scanf_s("%d", &n) != 1 || n <= 0 || n > 10) {
        printf("Error: n must be a natural number between 1 and 10.\n");
        return;
    }

    printf("Enter matrix elements (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++) {
        printf("Row %d: ", i);
        for (int j = 0; j < n; j++) {
            if (scanf_s("%d", &matrix[i][j]) != 1) {
                printf("Error: invalid input for element [%d][%d].\n", i, j);
                return;
            }
        }
    }

    printf("\nOriginal matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int temp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = temp;
        }
    }

    printf("\nTransposed matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    printf("\nVerification:\n");
    printf("Element [0][1] was %d, now is %d\n", matrix[1][0], matrix[0][1]);
    printf("Element [1][0] was %d, now is %d\n", matrix[0][1], matrix[1][0]);
}

void task6() {
    double A[100][100];
    int N, M, k;
    double sum = 0.0;
    int found = 0;

    printf("Enter number of rows N (N < 100): ");
    if (scanf_s("%d", &N) != 1 || N <= 0 || N >= 100) {
        printf("Error: N must be a natural number between 1 and 99.\n");
        return;
    }

    printf("Enter number of columns M (M < 100): ");
    if (scanf_s("%d", &M) != 1 || M <= 0 || M >= 100) {
        printf("Error: M must be a natural number between 1 and 99.\n");
        return;
    }

    printf("Enter number k: ");
    if (scanf_s("%d", &k) != 1) {
        printf("Error: invalid input for k.\n");
        return;
    }

    printf("Enter matrix elements (%d x %d):\n", N, M);
    for (int i = 0; i < N; i++) {
        printf("Row %d: ", i);
        for (int j = 0; j < M; j++) {
            if (scanf_s("%lf", &A[i][j]) != 1) {
                printf("Error: invalid input for element [%d][%d].\n", i, j);
                return;
            }
        }
    }

    printf("\nSearching for elements equal to %d:\n", k);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (A[i][j] == k) {
                sum += A[i][j];
                found = 1;
                printf("Found element A[%d][%d] = %.1f\n", i, j, A[i][j]);
            }
        }
    }

    if (found) {
        printf("\nSum of elements equal to %d: %.1f\n", k, sum);
    }
    else {
        printf("\nNo elements equal to %d found. Sum = 0\n", k);
    }
}


double determinant(double matrix[MAX_SIZE][MAX_SIZE], int n) {
    double det = 0;

    if (n == 1) {
        return matrix[0][0];
    }
    else if (n == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }
    else {
        double submatrix[MAX_SIZE][MAX_SIZE];

        for (int x = 0; x < n; x++) {
            int subi = 0;
            for (int i = 1; i < n; i++) {
                int subj = 0;
                for (int j = 0; j < n; j++) {
                    if (j == x) continue;
                    submatrix[subi][subj] = matrix[i][j];
                    subj++;
                }
                subi++;
            }
            double sign = (x % 2 == 0) ? 1 : -1;
            det += sign * matrix[0][x] * determinant(submatrix, n - 1);
        }
    }
    return det;
}

void task7() {
    double matrix[MAX_SIZE][MAX_SIZE];
    int n;

    printf("Enter size of square matrix n (n <= %d): ", MAX_SIZE);
    if (scanf_s("%d", &n) != 1 || n <= 0 || n > MAX_SIZE) {
        printf("Error: n must be a natural number between 1 and %d.\n", MAX_SIZE);
        return;
    }

    printf("Enter matrix elements (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++) {
        printf("Row %d: ", i);
        for (int j = 0; j < n; j++) {
            if (scanf_s("%lf", &matrix[i][j]) != 1) {
                printf("Error: invalid input for element [%d][%d].\n", i, j);
                return;
            }
        }
    }

    printf("\nEntered matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%8.2f ", matrix[i][j]);
        }
        printf("\n");
    }

    double det = determinant(matrix, n);
    printf("\nDeterminant of the matrix: %.2f\n", det);
}