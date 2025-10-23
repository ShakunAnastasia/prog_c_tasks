#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    char letter;  // a - h
    char digit;   // 1 - 8
} ChessSquare;

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    Point p1;
    Point p2;
} Rectangle;

typedef struct {
    int degree;
    double* coefficients;
} Polynomial;

bool is_valid_date(const Date* date) {
    if (date->year < 1) return false;
    if (date->month < 1 || date->month > 12) return false;

    int days_in_month;
    switch (date->month) {
    case 2:
        if ((date->year % 4 == 0 && date->year % 100 != 0) || (date->year % 400 == 0))
            days_in_month = 29;
        else
            days_in_month = 28;
        break;
    case 4: case 6: case 9: case 11:
        days_in_month = 30;
        break;
    default:
        days_in_month = 31;
        break;
    }
    return (date->day >= 1 && date->day <= days_in_month);
}

bool is_valid_chess_square(const ChessSquare* square) {
    return (square->letter >= 'a' && square->letter <= 'h' &&
        square->digit >= '1' && square->digit <= '8');
}

bool is_valid_rectangle(const Rectangle* rect) {
    return (rect->p1.x != rect->p2.x && rect->p1.y != rect->p2.y);
}

bool is_valid_polynomial(const Polynomial* poly) {
    return (poly->degree >= 0 && poly->coefficients != NULL);
}

void input_date(Date* date) {
    while (1) {
        printf("Enter date (day month year): ");
        if (scanf("%d %d %d", &date->day, &date->month, &date->year) == 3) {
            if (is_valid_date(date)) {
                break;
            }
        }
        printf("Error: Invalid date!\n");
        while (getchar() != '\n');
    }
}

void print_date(const Date* date) {
    printf("%02d.%02d.%04d", date->day, date->month, date->year);
}

void input_chess_square(ChessSquare* square) {
    while (1) {
        printf("Enter chess square (e.g., a5): ");
        if (scanf(" %c%c", &square->letter, &square->digit) == 2) {
            if (square->letter >= 'A' && square->letter <= 'H') {
                square->letter = square->letter - 'A' + 'a';
            }
            if (is_valid_chess_square(square)) {
                break;
            }
        }
        printf("Error: Invalid chess square!\n");
        while (getchar() != '\n');
    }
}

void print_chess_square(const ChessSquare* square) {
    printf("%c%c", square->letter, square->digit);
}

void input_rectangle(Rectangle* rect) {
    printf("Enter coordinates of two opposite vertices:\n");
    while (1) {
        printf("First vertex (x y): ");
        if (scanf("%lf %lf", &rect->p1.x, &rect->p1.y) != 2) {
            printf("Error: Invalid coordinates!\n");
            while (getchar() != '\n');
            continue;
        }
        printf("Second vertex (x y): ");
        if (scanf("%lf %lf", &rect->p2.x, &rect->p2.y) != 2) {
            printf("Error: Invalid coordinates!\n");
            while (getchar() != '\n');
            continue;
        }
        if (is_valid_rectangle(rect)) {
            Point temp;
            if (rect->p1.x > rect->p2.x) {
                temp.x = rect->p1.x;
                rect->p1.x = rect->p2.x;
                rect->p2.x = temp.x;
            }
            if (rect->p1.y > rect->p2.y) {
                temp.y = rect->p1.y;
                rect->p1.y = rect->p2.y;
                rect->p2.y = temp.y;
            }
            break;
        }
        printf("Error: This is not a rectangle with sides parallel to axes!\n");
    }
}

void print_rectangle(const Rectangle* rect) {
    printf("Rectangle: (%.2f, %.2f) - (%.2f, %.2f)",
        rect->p1.x, rect->p1.y, rect->p2.x, rect->p2.y);
}

double rectangle_area(const Rectangle* rect) {
    return fabs((rect->p2.x - rect->p1.x) * (rect->p2.y - rect->p1.y));
}

void input_polynomial(Polynomial* poly) {
    while (1) {
        printf("Enter polynomial degree: ");
        if (scanf("%d", &poly->degree) == 1 && poly->degree >= 0) {
            break;
        }
        printf("Error: Degree must be >= 0!\n");
        while (getchar() != '\n');
    }

    poly->coefficients = (double*)malloc((poly->degree + 1) * sizeof(double));
    if (poly->coefficients == NULL) {
        fprintf(stderr, "Error: Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    printf("Enter %d coefficient(s) from a0 to a%d:\n", poly->degree + 1, poly->degree);
    for (int i = 0; i <= poly->degree; i++) {
        printf("a%d: ", i);
        while (scanf("%lf", &poly->coefficients[i]) != 1) {
            printf("Error: Invalid coefficient! Try again: ");
            while (getchar() != '\n');
        }
    }
}

void print_polynomial(const Polynomial* poly) {
    if (!is_valid_polynomial(poly)) {
        printf("Invalid polynomial.\n");
        return;
    }

    printf("P(x) = ");
    bool first_term = true;

    for (int i = poly->degree; i >= 0; i--) {
        double coef = poly->coefficients[i];

        if (fabs(coef) < 1e-10) {
            if (i == 0 && first_term) {
                printf("0");
            }
            continue;
        }

        if (!first_term) {
            printf(coef > 0 ? " + " : " - ");
        }
        else if (coef < 0) {
            printf("-");
        }

        double abs_coef = fabs(coef);
        if (i == 0 || (fabs(abs_coef - 1.0) > 1e-10)) {
            printf("%.2f", abs_coef);
        }

        if (i > 0) {
            printf("x");
            if (i > 1) {
                printf("^%d", i);
            }
        }
        first_term = false;
    }
    printf("\n");
}

void free_polynomial(Polynomial* poly) {
    if (poly->coefficients != NULL) {
        free(poly->coefficients);
        poly->coefficients = NULL;
    }
    poly->degree = -1;
}

// Task 2

bool can_queen_move(const ChessSquare* from, const ChessSquare* to) {
    if (from->letter == to->letter && from->digit == to->digit) {
        return false;
    }

    if (from->digit == to->digit) {
        return true;
    }

    if (from->letter == to->letter) {
        return true;
    }

    int letter_diff = abs(from->letter - to->letter);
    int digit_diff = abs(from->digit - to->digit);
    if (letter_diff == digit_diff) {
        return true;
    }

    return false;
}

// Task 3

bool is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int days_in_month(int month, int year) {
    switch (month) {
    case 2: return is_leap_year(year) ? 29 : 28;
    case 4: case 6: case 9: case 11: return 30;
    default: return 31;
    }
}

Date get_tomorrow_date(const Date* date) {
    Date tomorrow = *date;
    tomorrow.day++;

    if (tomorrow.day > days_in_month(tomorrow.month, tomorrow.year)) {
        tomorrow.day = 1;
        tomorrow.month++;
        if (tomorrow.month > 12) {
            tomorrow.month = 1;
            tomorrow.year++;
        }
    }
    return tomorrow;
}

int get_day_of_week(const Date* date) {
    int q = date->day;
    int m = date->month;
    int y = date->year;

    if (m < 3) {
        m += 12;
        y--;
    }

    int k = y % 100;
    int j = y / 100;

    int h = (q + 13 * (m + 1) / 5 + k + k / 4 + j / 4 + 5 * j) % 7;

    return (h + 6) % 7;
}

const char* get_day_name(int day_of_week) {
    const char* days[] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };
    return days[day_of_week];
}

void task1() {
    printf("Task 1.\n\n");

    printf("a) Date structure:\n");
    Date date;
    input_date(&date);
    printf("Entered date: ");
    print_date(&date);
    printf("\n\n");

    printf("b) Chess square structure:\n");
    ChessSquare square;
    input_chess_square(&square);
    printf("Entered chess square: ");
    print_chess_square(&square);
    printf("\n\n");

    printf("c) Rectangle structure:\n");
    Rectangle rect;
    input_rectangle(&rect);
    print_rectangle(&rect);
    printf("\nArea: %.2f\n\n", rectangle_area(&rect));

    printf("d) Polynomial structure:\n");
    Polynomial poly;
    input_polynomial(&poly);
    printf("Entered polynomial: ");
    print_polynomial(&poly);
    free_polynomial(&poly);
}

void task2() {
    printf("Task 2.\n\n");

    ChessSquare from, to;

    printf("Enter starting square:\n");
    input_chess_square(&from);

    printf("Enter target square:\n");
    input_chess_square(&to);

    printf("\nQueen from ");
    print_chess_square(&from);
    printf(" to ");
    print_chess_square(&to);

    if (can_queen_move(&from, &to)) {
        printf(" - CAN move\n");
    }
    else {
        printf(" - CANNOT move\n");
    }
}

void task3() {
    printf("Task 3.\n\n");

    Date date;
    input_date(&date);

    printf("Entered date: ");
    print_date(&date);
    printf("\n");

    Date tomorrow = get_tomorrow_date(&date);
    printf("Tomorrow: ");
    print_date(&tomorrow);
    printf("\n");

    int day_of_week = get_day_of_week(&date);
    printf("Day of week: %s\n", get_day_name(day_of_week));
}

int main() {
    int choice;

    printf("Select task number (1-3):\n");
    printf("1 - Basic structures\n");
    printf("2 - Chess queen movement\n");
    printf("3 - Date operations\n");
    printf("Your choice: ");

    scanf_s("%d", &choice);
    while (getchar() != '\n');

    switch (choice) {
    case 1: task1(); break;
    case 2: task2(); break;
    case 3: task3(); break;
    default: printf("Invalid task number.\n");
    }

    printf("\nPress Enter to exit...");
    int ch = getchar();
    return 0;
}