#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void task1();
void task2();
void task3();
void task4();

int main() {

	int choice;
	printf("Enter task number (1-4): ");
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
	else {
		printf("Invalid task number.\n");
	}

}

void task1() {
    int n;
    int* array = NULL;
    int sum_of_squares = 0;

    printf("Enter natural number n: ");
    if (scanf_s("%d", &n) != 1 || n <= 0) {
        printf("Error: n must be a natural number.\n");
        return;
    }

    array = (int*)malloc(n * sizeof(int));
    if (array == NULL) {
        printf("Error: memory allocation failed.\n");
        return;
    }

    printf("Enter %d integer numbers:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Element %d: ", i);
        if (scanf_s("%d", array + i) != 1) {
            printf("Error: invalid input for element %d.\n", i);
            free(array);
            return;
        }
    }

    for (int i = 0; i < n; i++) {
        sum_of_squares += (*(array + i)) * (*(array + i));
    }

    printf("\nEntered array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", *(array + i));
    }
    printf("\n");

    printf("Sum of squares of elements: %d\n", sum_of_squares);

    free(array);
    array = NULL;
   
}


int is_perfect_square(int num) {
    if (num < 0) return 0;
    int root = (int)sqrt(num);
    return (root * root == num);
}

int is_perfect_cube(int num) {
    if (num < 0) {
        int root = (int)cbrt(num);
        return (root * root * root == num);
    }
    else {
        int root = (int)cbrt(num);
        return (root * root * root == num);
    }
}

int input_array(int* array, int max_size) {
    int count = 0;
    int num;

    printf("Enter integers (0 to stop, max %d elements):\n", max_size);

    while (count < max_size) {
        printf("Element %d: ", count);
        if (scanf_s("%d", &num) != 1) {
            printf("Error.\n");
            while (getchar() != '\n');
            continue;
        }

        if (num == 0) {
            break;
        }

        *(array + count) = num;
        count++;
    }

    return count;
}

void task2() {
    int array[100];
    int count;
    int squares_count = 0, cubes_count = 0;
    count = input_array(array, 100);

    if (count == 0) {
        printf("No elements were entered.\n");
        return;
    }

    printf("\nEntered array (%d elements): ", count);
    for (int i = 0; i < count; i++) {
        printf("%d ", *(array + i));
    }
    printf("\n");

    for (int i = 0; i < count; i++) {
        int current = *(array + i);

        if (is_perfect_square(current)) {
            squares_count++;
            printf("%d is perfect square\n", current);
        }

        if (is_perfect_cube(current)) {
            cubes_count++;
            printf("%d is perfect cube\n", current);
        }
    }

    printf("\nResults:\n");
    printf("Total elements: %d\n", count);
    printf("Perfect squares: %d\n", squares_count);
    printf("Perfect cubes: %d\n", cubes_count);

    int both_count = 0;
    for (int i = 0; i < count; i++) {
        int current = *(array + i);
        if (is_perfect_square(current) && is_perfect_cube(current)) {
            both_count++;
        }
    }
    printf("Numbers that are both squares and cubes: %d\n", both_count);
}


double* input_vector(int n) {
    if (n <= 0) {
        return NULL;
    }

    double* vector = (double*)malloc(n * sizeof(double));
    if (vector == NULL) {
        printf("Error: memory allocation failed for vector.\n");
        return NULL;
    }

    printf("Enter %d vector coordinates:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Coordinate %d: ", i + 1);
        if (scanf_s("%lf", vector + i) != 1) {
            printf("Error: invalid input for coordinate %d.\n", i + 1);
            free(vector);
            return NULL;
        }
    }

    return vector;
}

void print_vector(double* vector, int n, const char* name) {
    if (vector == NULL || n <= 0) {
        printf("%s: empty vector\n", name);
        return;
    }

    printf("%s = (", name);
    for (int i = 0; i < n; i++) {
        printf("%.2f", *(vector + i));
        if (i < n - 1) {
            printf(", ");
        }
    }
    printf(")\n");
}

double* vector_difference(double* vec1, double* vec2, int n) {
    if (vec1 == NULL || vec2 == NULL || n <= 0) {
        return NULL;
    }

    double* result = (double*)malloc(n * sizeof(double));
    if (result == NULL) {
        printf("Error: memory allocation failed for result vector.\n");
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        *(result + i) = *(vec1 + i) - *(vec2 + i);
    }

    return result;
}

void free_vector(double* vector) {
    if (vector != NULL) {
        free(vector);
    }
}

void task3() {
    int n;
    double* vector1 = NULL, * vector2 = NULL, * difference = NULL;

    printf("Enter vector dimension n: ");
    if (scanf_s("%d", &n) != 1 || n <= 0) {
        printf("Error: n must be a positive integer.\n");
        return;
    }

    printf("\nFirst vector:\n");
    vector1 = input_vector(n);
    if (vector1 == NULL) {
        printf("Failed to input first vector.\n");
        return;
    }

    printf("\nSecond vector:\n");
    vector2 = input_vector(n);
    if (vector2 == NULL) {
        printf("Failed to input second vector.\n");
        free_vector(vector1);
        return;
    }

    printf("\nInput vectors:\n");
    print_vector(vector1, n, "Vector 1");
    print_vector(vector2, n, "Vector 2");

    printf("\nVector difference:\n");
    difference = vector_difference(vector1, vector2, n);

    if (difference != NULL) {
        print_vector(difference, n, "Difference (V1 - V2)");

        double max_diff = 0;
        for (int i = 0; i < n; i++) {
            double diff = *(difference + i);
            if (diff > max_diff) {
                max_diff = diff;
            }
        }
        printf("Maximum difference: %.2f\n", max_diff);
    }
    else {
        printf("Error: could not compute vector difference.\n");
    }

    printf("\nMemory cleanup:\n");
    free_vector(vector1);
    free_vector(vector2);
    free_vector(difference);

    vector1 = NULL;
    vector2 = NULL;
    difference = NULL;

    printf("Memory successfully freed. Program completed without memory leaks.\n");
}

double** allocate_matrix_2d(int n) {
    if (n <= 0) return NULL;

    double** matrix = (double**)malloc(n * sizeof(double*));
    if (matrix == NULL) return NULL;

    for (int i = 0; i < n; i++) {
        matrix[i] = (double*)malloc(n * sizeof(double));
        if (matrix[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return NULL;
        }
        for (int j = 0; j < n; j++) {
            matrix[i][j] = 0.0;
        }
    }
    return matrix;
}

double** input_matrix_2d(int n) {
    double** matrix = allocate_matrix_2d(n);
    if (matrix == NULL) {
        printf("Error: memory allocation failed for matrix.\n");
        return NULL;
    }

    printf("Enter %dx%d matrix elements:\n", n, n);
    for (int i = 0; i < n; i++) {
        printf("Row %d: ", i + 1);
        for (int j = 0; j < n; j++) {
            if (scanf_s("%lf", &matrix[i][j]) != 1) {
                printf("Error: invalid input for element [%d][%d].\n", i, j);
                for (int k = 0; k <= i; k++) {
                    free(matrix[k]);
                }
                free(matrix);
                return NULL;
            }
        }
    }
    return matrix;
}

double** multiply_matrices_2d(double** A, double** B, int n) {
    if (A == NULL || B == NULL || n <= 0) return NULL;

    double** result = allocate_matrix_2d(n);
    if (result == NULL) return NULL;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = 0.0;
            for (int k = 0; k < n; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

void print_matrix_2d(double** matrix, int n, const char* name) {
    if (matrix == NULL || n <= 0) {
        printf("%s: empty matrix\n", name);
        return;
    }

    printf("%s:\n", name);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%8.2f ", matrix[i][j]);
        }
        printf("\n");
    }
}

void free_matrix_2d(double** matrix, int n) {
    if (matrix != NULL) {
        for (int i = 0; i < n; i++) {
            if (matrix[i] != NULL) {
                free(matrix[i]);
            }
        }
        free(matrix);
    }
}

double* allocate_matrix_linear(int n) {
    if (n <= 0) return NULL;
    double* matrix = (double*)calloc(n * n, sizeof(double));
    return matrix;
}

double* input_matrix_linear(int n) {
    double* matrix = allocate_matrix_linear(n);
    if (matrix == NULL) {
        printf("Error: memory allocation failed for matrix.\n");
        return NULL;
    }

    printf("Enter %dx%d matrix elements:\n", n, n);
    for (int i = 0; i < n; i++) {
        printf("Row %d: ", i + 1);
        for (int j = 0; j < n; j++) {
            if (scanf_s("%lf", matrix + i * n + j) != 1) {
                printf("Error: invalid input for element [%d][%d].\n", i, j);
                free(matrix);
                return NULL;
            }
        }
    }
    return matrix;
}

double* multiply_matrices_linear(double* A, double* B, int n) {
    if (A == NULL || B == NULL || n <= 0) return NULL;

    double* result = allocate_matrix_linear(n);
    if (result == NULL) return NULL;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double sum = 0.0;
            for (int k = 0; k < n; k++) {
                sum += *(A + i * n + k) * *(B + k * n + j);
            }
            *(result + i * n + j) = sum;
        }
    }
    return result;
}

void print_matrix_linear(double* matrix, int n, const char* name) {
    if (matrix == NULL || n <= 0) {
        printf("%s: empty matrix\n", name);
        return;
    }

    printf("%s:\n", name);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%8.2f ", *(matrix + i * n + j));
        }
        printf("\n");
    }
}

void free_matrix_linear(double* matrix) {
    if (matrix != NULL) {
        free(matrix);
    }
}


void task4() {
    int n;
    int representation;

    printf("Choose matrix representation:\n");
    printf("1 - Two-dimensional array\n");
    printf("2 - Linear array\n");
    printf("Your choice: ");
    if (scanf_s("%d", &representation) != 1 || (representation != 1 && representation != 2)) {
        printf("Error: invalid choice.\n");
        return;
    }

    printf("Enter matrix size n: ");
    if (scanf_s("%d", &n) != 1 || n <= 0) {
        printf("Error: n must be a positive integer.\n");
        return;
    }

    if (representation == 1) {
        double** matrix1 = NULL, ** matrix2 = NULL, ** product = NULL;

        printf("\nFirst matrix (2D array):\n");
        matrix1 = input_matrix_2d(n);
        if (matrix1 == NULL) return;

        printf("\nSecond matrix (2D array):\n");
        matrix2 = input_matrix_2d(n);
        if (matrix2 == NULL) {
            free_matrix_2d(matrix1, n);
            return;
        }

        printf("\nInput matrices:\n");
        print_matrix_2d(matrix1, n, "Matrix A");
        print_matrix_2d(matrix2, n, "Matrix B");

        printf("\nMatrix product:\n");
        product = multiply_matrices_2d(matrix1, matrix2, n);
        if (product != NULL) {
            print_matrix_2d(product, n, "Product A x B");
        }
        else {
            printf("Error: could not compute matrix product.\n");
        }

        free_matrix_2d(matrix1, n);
        free_matrix_2d(matrix2, n);
        free_matrix_2d(product, n);

    }
    else {
        double* matrix1 = NULL, * matrix2 = NULL, * product = NULL;

        printf("\nFirst matrix (linear array):\n");
        matrix1 = input_matrix_linear(n);
        if (matrix1 == NULL) return;

        printf("\nSecond matrix (linear array):\n");
        matrix2 = input_matrix_linear(n);
        if (matrix2 == NULL) {
            free_matrix_linear(matrix1);
            return;
        }

        printf("\nInput matrices:\n");
        print_matrix_linear(matrix1, n, "Matrix A");
        print_matrix_linear(matrix2, n, "Matrix B");

        printf("\nMatrix product:\n");
        product = multiply_matrices_linear(matrix1, matrix2, n);
        if (product != NULL) {
            print_matrix_linear(product, n, "Product A x B");
        }
        else {
            printf("Error: could not compute matrix product.\n");
        }

        free_matrix_linear(matrix1);
        free_matrix_linear(matrix2);
        free_matrix_linear(product);
    }

    printf("\nProgram completed successfully without memory leaks.\n");
}