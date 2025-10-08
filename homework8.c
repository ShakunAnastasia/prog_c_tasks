#include <stdio.h>

int main() {
    int matrix[10][10];
    int n, m;

    printf("Enter number of rows n (n <= 10): ");
    if (scanf_s("%d", &n) != 1 || n <= 0 || n > 10) {
        printf("Error: n must be a natural number between 1 and 10.\n");
        return;
    }

    printf("Enter number of columns m (m <= 10): ");
    if (scanf_s("%d", &m) != 1 || m <= 0 || m > 10) {
        printf("Error: m must be a natural number between 1 and 10.\n");
        return;
    }

    printf("Enter matrix elements (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++) {
        printf("Row %d: ", i);
        for (int j = 0; j < m; j++) {
            if (scanf_s("%d", &matrix[i][j]) != 1) {
                printf("Error: invalid input for element [%d][%d].\n", i, j);
                return;
            }
        }
    }

    printf("\nOriginal matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    if (n > 1) {
        int temp[10];

        for (int j = 0; j < m; j++) {
            temp[j] = matrix[n - 1][j];
        }

        for (int i = n - 1; i > 0; i--) {
            for (int j = 0; j < m; j++) {
                matrix[i][j] = matrix[i - 1][j];
            }
        }

        for (int j = 0; j < m; j++) {
            matrix[0][j] = temp[j];
        }

        printf("\nMatrix after cyclic permutation:\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                printf("%d ", matrix[i][j]);
            }
            printf("\n");
        }
    }
    else {
        printf("\nMatrix has only one row - no permutation needed.\n");
    }
}