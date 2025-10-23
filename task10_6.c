#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define M_PI 3.14159265358979323846

// a)
typedef struct {
    int hrn;
    int kop;
} Money;

void inputMoney(Money* money) {
    printf("Enter hrn: ");
    scanf("%d", &money->hrn);
    printf("Enter kop: ");
    scanf("%d", &money->kop);

    if (money->kop >= 100) {
        money->hrn += money->kop / 100;
        money->kop %= 100;
    }
}

void printMoney(const Money* money) {
    printf("%d UAH %02d kop\n", money->hrn, money->kop);
}

// b)
typedef struct {
    int hours;
    int minutes;
    int seconds;
} Time;

void inputTime(Time* time) {
    printf("Enter hours (0-23): ");
    scanf("%d", &time->hours);
    printf("Enter minutes (0-59): ");
    scanf("%d", &time->minutes);
    printf("Enter seconds (0-59): ");
    scanf("%d", &time->seconds);

    time->minutes += time->seconds / 60;
    time->seconds %= 60;
    time->hours += time->minutes / 60;
    time->minutes %= 60;
    time->hours %= 24;
}

void printTime(const Time* time) {
    printf("%02d:%02d:%02d\n", time->hours, time->minutes, time->seconds);
}

// c)
typedef struct {
    int day;
    int month;
    int year;
    Time time;
} FullDate;

void inputFullDate(FullDate* date) {
    printf("Enter day: ");
    scanf("%d", &date->day);
    printf("Enter month: ");
    scanf("%d", &date->month);
    printf("Enter year: ");
    scanf("%d", &date->year);
    printf("Enter time:\n");
    inputTime(&date->time);
}

void printFullDate(const FullDate* date) {
    printf("%02d.%02d.%04d %02d:%02d:%02d\n",
        date->day, date->month, date->year,
        date->time.hours, date->time.minutes, date->time.seconds);
}

// d)
typedef struct {
    char city[50];
    char street[50];
    int building;
    int apartment;
} Address;

void inputAddress(Address* address) {
    printf("Enter city: ");
    scanf("%49s", address->city);
    printf("Enter street: ");
    scanf("%49s", address->street);
    printf("Enter building number: ");
    scanf("%d", &address->building);
    printf("Enter apartment number: ");
    scanf("%d", &address->apartment);
}

void printAddress(const Address* address) {
    printf("%s, %s St., Building %d, Apt. %d\n",
        address->city, address->street, address->building, address->apartment);
}

// e)
typedef struct {
    char subject[50];
    char teacher[50];
    int groupNumber;
    char dayOfWeek[20];
    Time startTime;
    Time endTime;
    char classroom[20];
} Seminar;

void inputSeminar(Seminar* seminar) {
    printf("Enter subject: ");
    scanf("%49s", seminar->subject);
    printf("Enter teacher: ");
    scanf("%49s", seminar->teacher);
    printf("Enter group number: ");
    scanf("%d", &seminar->groupNumber);
    printf("Enter day of week: ");
    scanf("%19s", seminar->dayOfWeek);
    printf("Enter start time:\n");
    inputTime(&seminar->startTime);
    printf("Enter end time:\n");
    inputTime(&seminar->endTime);
    printf("Enter classroom: ");
    scanf("%19s", seminar->classroom);
}

void printSeminar(const Seminar* seminar) {
    printf("Subject: %s\n", seminar->subject);
    printf("Teacher: %s\n", seminar->teacher);
    printf("Group: %d\n", seminar->groupNumber);
    printf("Day: %s\n", seminar->dayOfWeek);
    printf("Time: ");
    printTime(&seminar->startTime);
    printf(" - ");
    printTime(&seminar->endTime);
    printf("Classroom: %s\n", seminar->classroom);
}

// f)
typedef struct {
    char code[20];
    char author[50];
    char title[100];
    int readerTicket;
    char readerName[50];
    FullDate requestDate;
} BookRequest;

void inputBookRequest(BookRequest* request) {
    printf("Book Information\n");
    printf("Enter book code: ");
    scanf("%19s", request->code);
    printf("Enter author: ");
    scanf("%49s", request->author);
    printf("Enter title: ");
    scanf("%99s", request->title);

    printf("\nReader Information\n");
    printf("Enter reader ticket number: ");
    scanf("%d", &request->readerTicket);
    printf("Enter reader name: ");
    scanf("%49s", request->readerName);

    printf("\nRequest Date\n");
    inputFullDate(&request->requestDate);
}

void printBookRequest(const BookRequest* request) {
    printf("Book Request Form\n");
    printf("Book: %s by %s (Code: %s)\n",
        request->title, request->author, request->code);
    printf("Reader: %s (Ticket: %d)\n",
        request->readerName, request->readerTicket);
    printf("Request Date: ");
    printFullDate(&request->requestDate);
}

// g)
typedef struct {
    double radius;
    double centerX;
    double centerY;
} Circle;

void inputCircle(Circle* circle) {
    printf("Enter circle radius: ");
    scanf("%lf", &circle->radius);
    printf("Enter center X coordinate: ");
    scanf("%lf", &circle->centerX);
    printf("Enter center Y coordinate: ");
    scanf("%lf", &circle->centerY);
}

void printCircle(const Circle* circle) {
    printf("Circle: Center(%.2f, %.2f), Radius: %.2f\n",
        circle->centerX, circle->centerY, circle->radius);
}

double circleArea(const Circle* circle) {
    return M_PI * circle->radius * circle->radius;
}

// h)
typedef struct {
    double radius;
    double centerX;
    double centerY;
    double centerZ;
} Sphere;

void inputSphere(Sphere* sphere) {
    printf("Enter sphere radius: ");
    scanf("%lf", &sphere->radius);
    printf("Enter center X coordinate: ");
    scanf("%lf", &sphere->centerX);
    printf("Enter center Y coordinate: ");
    scanf("%lf", &sphere->centerY);
    printf("Enter center Z coordinate: ");
    scanf("%lf", &sphere->centerZ);
}

void printSphere(const Sphere* sphere) {
    printf("Sphere: Center(%.2f, %.2f, %.2f), Radius: %.2f\n",
        sphere->centerX, sphere->centerY, sphere->centerZ, sphere->radius);
}

double sphereVolume(const Sphere* sphere) {
    return (4.0 / 3.0) * M_PI * pow(sphere->radius, 3);
}

// i)
typedef struct {
    double width;   // x
    double height;  // y  
    double depth;   // z
    double centerX;
    double centerY;
    double centerZ;
} RectParallelepiped;

void inputRectParallelepiped(RectParallelepiped* para) {
    printf("Enter width (x): ");
    scanf("%lf", &para->width);
    printf("Enter height (y): ");
    scanf("%lf", &para->height);
    printf("Enter depth (z): ");
    scanf("%lf", &para->depth);
    printf("Enter center X coordinate: ");
    scanf("%lf", &para->centerX);
    printf("Enter center Y coordinate: ");
    scanf("%lf", &para->centerY);
    printf("Enter center Z coordinate: ");
    scanf("%lf", &para->centerZ);
}

void printRectParallelepiped(const RectParallelepiped* para) {
    printf("Parallelepiped: Center(%.2f, %.2f, %.2f), Size(%.2f x %.2f x %.2f)\n",
        para->centerX, para->centerY, para->centerZ,
        para->width, para->height, para->depth);
}

double paraVolume(const RectParallelepiped* para) {
    return para->width * para->height * para->depth;
}

// j)
typedef struct {
    int size;
    double* data;
} Vector;

void inputVector(Vector* vector) {
    printf("Enter vector size: ");
    scanf("%d", &vector->size);

    vector->data = (double*)malloc(vector->size * sizeof(double));
    if (vector->data == NULL) {
        printf("Memory allocation failed!\n");
        vector->size = 0;
        return;
    }

    printf("Enter %d vector elements:\n", vector->size);
    for (int i = 0; i < vector->size; i++) {
        printf("Element %d: ", i + 1);
        scanf("%lf", &vector->data[i]);
    }
}

void printVector(const Vector* vector) {
    printf("Vector[%d]: [", vector->size);
    for (int i = 0; i < vector->size; i++) {
        printf("%.2f", vector->data[i]);
        if (i < vector->size - 1) printf(", ");
    }
    printf("]\n");
}

void freeVector(Vector* vector) {
    free(vector->data);
    vector->size = 0;
}

// k)
typedef struct {
    int rows;
    int cols;
    double** data;
} Matrix;

void inputMatrix(Matrix* matrix) {
    printf("Enter matrix rows: ");
    scanf("%d", &matrix->rows);
    printf("Enter matrix columns: ");
    scanf("%d", &matrix->cols);

    // Allocate memory for matrix
    matrix->data = (double**)malloc(matrix->rows * sizeof(double*));
    for (int i = 0; i < matrix->rows; i++) {
        matrix->data[i] = (double*)malloc(matrix->cols * sizeof(double));
    }

    printf("Enter matrix elements (%d x %d):\n", matrix->rows, matrix->cols);
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            printf("Element [%d][%d]: ", i + 1, j + 1);
            scanf("%lf", &matrix->data[i][j]);
        }
    }
}

void printMatrix(const Matrix* matrix) {
    printf("Matrix %dx%d:\n", matrix->rows, matrix->cols);
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            printf("%8.2f", matrix->data[i][j]);
        }
        printf("\n");
    }
}

void freeMatrix(Matrix* matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        free(matrix->data[i]);
    }
    free(matrix->data);
    matrix->rows = 0;
    matrix->cols = 0;
}

// l)
typedef struct {
    int vertexCount;
    double* xCoords;
    double* yCoords;
} Polygon;

void inputPolygon(Polygon* poly) {
    printf("Enter number of polygon vertices: ");
    scanf("%d", &poly->vertexCount);

    poly->xCoords = (double*)malloc(poly->vertexCount * sizeof(double));
    poly->yCoords = (double*)malloc(poly->vertexCount * sizeof(double));

    printf("Enter coordinates for %d vertices:\n", poly->vertexCount);
    for (int i = 0; i < poly->vertexCount; i++) {
        printf("Vertex %d - X: ", i + 1);
        scanf("%lf", &poly->xCoords[i]);
        printf("Vertex %d - Y: ", i + 1);
        scanf("%lf", &poly->yCoords[i]);
    }
}

void printPolygon(const Polygon* poly) {
    printf("Polygon with %d vertices:\n", poly->vertexCount);
    for (int i = 0; i < poly->vertexCount; i++) {
        printf("Vertex %d: (%.2f, %.2f)\n", i + 1, poly->xCoords[i], poly->yCoords[i]);
    }
}

void freePolygon(Polygon* poly) {
    free(poly->xCoords);
    free(poly->yCoords);
    poly->vertexCount = 0;
}

// main
void demonstrateAllTypes() {
    printf("DEMONSTRATION\n\n");

    printf("1. MONEY:\n");
    Money money;
    inputMoney(&money);
    printf("Entered: ");
    printMoney(&money);
    printf("\n");

    printf("2. TIME:\n");
    Time time;
    inputTime(&time);
    printf("Entered: ");
    printTime(&time);
    printf("\n");

    printf("3. FULL DATE:\n");
    FullDate date;
    inputFullDate(&date);
    printf("Entered: ");
    printFullDate(&date);
    printf("\n");

    printf("4. ADDRESS:\n");
    Address address;
    inputAddress(&address);
    printf("Entered: ");
    printAddress(&address);
    printf("\n");

    printf("5. SEMINAR:\n");
    Seminar seminar;
    inputSeminar(&seminar);
    printf("Entered:\n");
    printSeminar(&seminar);
    printf("\n");

    printf("6. BOOK REQUEST:\n");
    BookRequest bookReq;
    inputBookRequest(&bookReq);
    printBookRequest(&bookReq);
    printf("\n");

    printf("7. CIRCLE:\n");
    Circle circle;
    inputCircle(&circle);
    printCircle(&circle);
    printf("Area: %.2f\n\n", circleArea(&circle));

    printf("8. SPHERE:\n");
    Sphere sphere;
    inputSphere(&sphere);
    printSphere(&sphere);
    printf("Volume: %.2f\n\n", sphereVolume(&sphere));

    printf("9. RECTANGULAR PARALLELEPIPED:\n");
    RectParallelepiped para;
    inputRectParallelepiped(&para);
    printRectParallelepiped(&para);
    printf("Volume: %.2f\n\n", paraVolume(&para));

    printf("10. VECTOR:\n");
    Vector vector;
    inputVector(&vector);
    printVector(&vector);
    freeVector(&vector);
    printf("\n");

    printf("11. MATRIX:\n");
    Matrix matrix;
    inputMatrix(&matrix);
    printMatrix(&matrix);
    freeMatrix(&matrix);
    printf("\n");

    printf("12. POLYGON:\n");
    Polygon polygon;
    inputPolygon(&polygon);
    printPolygon(&polygon);
    freePolygon(&polygon);

    printf("\nTHE END\n");
}

int main() {
    demonstrateAllTypes();
    return 0;
}