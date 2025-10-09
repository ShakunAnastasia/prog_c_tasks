#include <stdio.h>
#include <stdlib.h>

void task9_9_b();
void task9_9_ch();

int main() {

	int choice;
	printf("Enter 1 for task 9.9 b, 2 for task 9.9 ch: ");
	scanf_s("%d", &choice);

	if (choice == 1) {
		task9_9_b();
	}
	else if (choice == 2) {
		task9_9_ch();
	}
	else {
		printf("Invalid task number.\n");
	}
}

void task9_9_b() {
    int N, M;
    int** matrix = NULL;
    int fill_method;

    printf("Enter number of rows N: ");
    if (scanf_s("%d", &N) != 1 || N <= 0) {
        printf("Error: N must be a natural number.\n");
        return;
    }

    printf("Enter number of columns M: ");
    if (scanf_s("%d", &M) != 1 || M <= 0) {
        printf("Error: M must be a natural number.\n");
        return;
    }
    printf("\nChoose filling method:\n");
    printf("1 - Fill with random numbers (0-99)\n");
    printf("2 - Fill from console input\n");
    printf("Your choice (1 or 2): ");
    if (scanf_s("%d", &fill_method) != 1 || (fill_method != 1 && fill_method != 2)) {
        printf("Error: invalid choice. Please enter 1 or 2.\n");
        return;
    }

    matrix = (int**)malloc(N * sizeof(int*));
    if (matrix == NULL) {
        printf("Error: memory allocation failed for rows.\n");
        return;
    }

    for (int i = 0; i < N; i++) {
        matrix[i] = (int*)malloc(M * sizeof(int));
        if (matrix[i] == NULL) {
            printf("Error: memory allocation failed for columns in row %d.\n", i);
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return;
        }
    }

    if (fill_method == 1) {
        printf("\nFilling matrix with random numbers (0-99)...\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                matrix[i][j] = rand() % 100;
            }
        }
    }
    else {
        printf("\nEnter matrix elements (%d x %d):\n", N, M);
        for (int i = 0; i < N; i++) {
            printf("Row %d (enter %d numbers separated by spaces): ", i + 1, M);
            for (int j = 0; j < M; j++) {
                if (scanf_s("%d", &matrix[i][j]) != 1) {
                    printf("Error: invalid input for element [%d][%d].\n", i, j);
                    for (int k = 0; k < N; k++) {
                        free(matrix[k]);
                    }
                    free(matrix);
                    return;
                }
            }
        }
    }

    printf("\nMatrix (%d x %d):\n", N, M);
    printf("     ");
    for (int j = 0; j < M; j++) {
        printf("%6d ", j + 1);
    }
    printf("\n");

    for (int i = 0; i < N; i++) {
        printf("%4d ", i + 1);
        for (int j = 0; j < M; j++) {
            printf("%6d ", matrix[i][j]);
        }
        printf("\n");
    }

    printf("\nColumn sums\n");
    int max_sum = 0;
    int max_column = 0;

    for (int j = 0; j < M; j++) {
        int column_sum = 0;
        for (int i = 0; i < N; i++) {
            column_sum += matrix[i][j];
        }

        printf("Column %d sum: %d\n", j + 1, column_sum);

        if (column_sum > max_sum) {
            max_sum = column_sum;
            max_column = j;
        }
    }

    printf("\nColumn with maximum sum:\n");
    printf("Column %d has maximum sum: %d\n", max_column + 1, max_sum);
    printf("Elements of column %d:\n", max_column + 1);
    for (int i = 0; i < N; i++) {
        printf("Row %d: %d\n", i + 1, matrix[i][max_column]);
    }

    printf("\nMemory cleanup:\n");
    for (int i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);

    printf("Memory successfully freed. Program completed.\n");
}


void task9_9_ch() {
    int N, M;
    int** matrix = NULL;
    int choice;

    printf("Enter number of rows N: ");
    if (scanf_s("%d", &N) != 1 || N <= 0) {
        printf("Error: N must be a natural number.\n");
        return;
    }

    printf("Enter number of columns M: ");
    if (scanf_s("%d", &M) != 1 || M <= 0) {
        printf("Error: M must be a natural number.\n");
        return;
    }

    printf("\nChoose filling method:\n");
    printf("1 - Random numbers (0-99)\n");
    printf("2 - Manual input from console\n");
    printf("Your choice: ");
    if (scanf_s("%d", &choice) != 1 || (choice != 1 && choice != 2)) {
        printf("Error: invalid choice.\n");
        return;
    }

    matrix = (int**)malloc(N * sizeof(int*));
    if (matrix == NULL) {
        printf("Error: memory allocation failed for rows.\n");
        return;
    }

    for (int i = 0; i < N; i++) {
        matrix[i] = (int*)malloc(M * sizeof(int));
        if (matrix[i] == NULL) {
            printf("Error: memory allocation failed for columns in row %d.\n", i);
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return;
        }
    }

    if (choice == 1) {
        printf("\nFilling matrix with random numbers (0-99):\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                matrix[i][j] = rand() % 100;
            }
        }
    }
    else {
        printf("\nEnter matrix elements (%d x %d):\n", N, M);
        for (int i = 0; i < N; i++) {
            printf("Row %d: ", i + 1);
            for (int j = 0; j < M; j++) {
                if (scanf_s("%d", &matrix[i][j]) != 1) {
                    printf("Error: invalid input for element [%d][%d].\n", i, j);
                    for (int k = 0; k < N; k++) {
                        free(matrix[k]);
                    }
                    free(matrix);
                    return;
                }
            }
        }
    }

    printf("\nMatrix (%d x %d):\n", N, M);
    printf("     ");
    for (int j = 0; j < M; j++) {
        printf("%6d ", j + 1);
    }
    printf("\n");

    for (int i = 0; i < N; i++) {
        printf("%4d ", i + 1);
        for (int j = 0; j < M; j++) {
            printf("%6d ", matrix[i][j]);
        }
        printf("\n");
    }

    printf("\nColumn sums:\n");
    int* column_sums = (int*)malloc(M * sizeof(int));
    if (column_sums == NULL) {
        printf("Error: memory allocation failed for column sums.\n");
        for (int i = 0; i < N; i++) {
            free(matrix[i]);
        }
        free(matrix);
        return;
    }

    int max_sum = 0;
    int max_column = 0;

    for (int j = 0; j < M; j++) {
        column_sums[j] = 0;
        for (int i = 0; i < N; i++) {
            column_sums[j] += matrix[i][j];
        }

        printf("Column %d sum: %d\n", j + 1, column_sums[j]);

        if (j == 0 || column_sums[j] > max_sum) {
            max_sum = column_sums[j];
            max_column = j;
        }
    }

    printf("\nColumn with maximum sum:\n");
    printf("Column %d has maximum sum: %d\n", max_column + 1, max_sum);
    printf("Elements of column %d:\n", max_column + 1);
    for (int i = 0; i < N; i++) {
        printf("Row %d: %d\n", i + 1, matrix[i][max_column]);
    }

    printf("\nAdditional information:\n");
    printf("Number of columns with maximum sum (%d): ", max_sum);
    int count_max_columns = 0;
    for (int j = 0; j < M; j++) {
        if (column_sums[j] == max_sum) {
            count_max_columns++;
            if (count_max_columns > 1) {
                printf(", ");
            }
            printf("%d", j + 1);
        }
    }
    printf(" (%d column%s total)\n", count_max_columns, count_max_columns == 1 ? "" : "s");

    printf("\nMemory cleanup:\n");
    free(column_sums);
    for (int i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);

    printf("Memory successfully freed. Program completed.\n");
}