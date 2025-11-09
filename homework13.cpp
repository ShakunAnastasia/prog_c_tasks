#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <memory>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// task 4

class Point {
private:
    double x, y;
    bool isEmpty;

public:
    Point() : x(0), y(0), isEmpty(true) {}
    Point(double x_val, double y_val) : x(x_val), y(y_val), isEmpty(false) {}

    bool getIsEmpty() const { return isEmpty; }
    double getX() const { return x; }
    double getY() const { return y; }

    void input() {
        cout << "Enter x coordinate: ";
        cin >> x;
        cout << "Enter y coordinate: ";
        cin >> y;
        isEmpty = false;
    }

    void display() const {
        if (isEmpty) {
            cout << "Empty Point";
        }
        else {
            cout << "(" << x << ", " << y << ")";
        }
    }
};

class Segment {
private:
    Point p1, p2;

public:
    void input() {
        cout << "Enter first point:\n";
        p1.input();
        cout << "Enter second point:\n";
        p2.input();
    }

    void display() const {
        cout << "Segment: ";
        p1.display();
        cout << " - ";
        p2.display();
        cout << endl;
    }

    Point getMidpoint() const {
        if (p1.getIsEmpty() || p2.getIsEmpty()) return Point();
        return Point((p1.getX() + p2.getX()) / 2, (p1.getY() + p2.getY()) / 2);
    }

    double getLength() const {
        if (p1.getIsEmpty() || p2.getIsEmpty()) return 0;
        double dx = p2.getX() - p1.getX();
        double dy = p2.getY() - p1.getY();
        return sqrt(dx * dx + dy * dy);
    }
};

class Triangle {
private:
    Point p1, p2, p3;

public:
    void input() {
        cout << "Enter first point:\n";
        p1.input();
        cout << "Enter second point:\n";
        p2.input();
        cout << "Enter third point:\n";
        p3.input();
    }

    void display() const {
        cout << "Triangle: ";
        p1.display();
        cout << ", ";
        p2.display();
        cout << ", ";
        p3.display();
        cout << endl;
    }

    double getPerimeter() const {
        double a = sqrt(pow(p2.getX() - p1.getX(), 2) + pow(p2.getY() - p1.getY(), 2));
        double b = sqrt(pow(p3.getX() - p2.getX(), 2) + pow(p3.getY() - p2.getY(), 2));
        double c = sqrt(pow(p1.getX() - p3.getX(), 2) + pow(p1.getY() - p3.getY(), 2));
        return a + b + c;
    }

    double getArea() const {
        double a = sqrt(pow(p2.getX() - p1.getX(), 2) + pow(p2.getY() - p1.getY(), 2));
        double b = sqrt(pow(p3.getX() - p2.getX(), 2) + pow(p3.getY() - p2.getY(), 2));
        double c = sqrt(pow(p1.getX() - p3.getX(), 2) + pow(p1.getY() - p3.getY(), 2));
        double s = (a + b + c) / 2;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }
};

void task4() {
    cout << "\n~~~ TASK 4: Points, Segments, Triangles." << endl;

    Segment seg;
    seg.input();
    seg.display();

    Point mid = seg.getMidpoint();
    cout << "Midpoint: ";
    mid.display();
    cout << endl;

    cout << "Length: " << seg.getLength() << endl;

    Triangle tri;
    tri.input();
    tri.display();
    cout << "Perimeter: " << tri.getPerimeter() << endl;
    cout << "Area: " << tri.getArea() << endl;
}

// task 5
class Circle {
private:
    double centerX, centerY, radius;

public:
    Circle() : centerX(0), centerY(0), radius(1) {}
    Circle(double x, double y, double r) : centerX(x), centerY(y), radius(r) {
        if (r <= 0) throw invalid_argument("Radius must be positive");
    }

    void input() {
        cout << "Enter center x: ";
        cin >> centerX;
        cout << "Enter center y: ";
        cin >> centerY;
        cout << "Enter radius: ";
        cin >> radius;
        if (radius <= 0) throw invalid_argument("Radius must be positive");
    }

    void display() const {
        cout << "Circle: center(" << centerX << ", " << centerY << "), radius=" << radius;
    }

    double getDiameter() const { return 2 * radius; }
    double getArea() const { return M_PI * radius * radius; }
    double getPerimeter() const { return 2 * M_PI * radius; }
};

void task5() {
    cout << "\n~~~ TASK 5: Circles." << endl;

    Circle c;
    c.input();
    c.display();
    cout << endl;
    cout << "Diameter: " << c.getDiameter() << endl;
    cout << "Area: " << c.getArea() << endl;
    cout << "Perimeter: " << c.getPerimeter() << endl;
}

// task 6
class Rectangle {
private:
    double x, y, width, height;

public:
    Rectangle() : x(0), y(0), width(1), height(1) {}
    Rectangle(double x_val, double y_val, double w, double h)
        : x(x_val), y(y_val), width(w), height(h) {
        if (w <= 0 || h <= 0) throw invalid_argument("Dimensions must be positive");
    }

    void input() {
        cout << "Enter top-left x: ";
        cin >> x;
        cout << "Enter top-left y: ";
        cin >> y;
        cout << "Enter width: ";
        cin >> width;
        cout << "Enter height: ";
        cin >> height;
        if (width <= 0 || height <= 0) throw invalid_argument("Dimensions must be positive");
    }

    void display() const {
        cout << "Rectangle: (" << x << ", " << y << "), w=" << width << ", h=" << height;
    }

    double getWidth() const { return width; }
    double getHeight() const { return height; }
    double getArea() const { return width * height; }
    double getPerimeter() const { return 2 * (width + height); }
};

void task6() {
    cout << "\n~~~ TASK 6: Rectangles." << endl;

    Rectangle rect;
    rect.input();
    rect.display();
    cout << endl;
    cout << "Width: " << rect.getWidth() << endl;
    cout << "Height: " << rect.getHeight() << endl;
    cout << "Area: " << rect.getArea() << endl;
    cout << "Perimeter: " << rect.getPerimeter() << endl;
}

// task 7
class Triangle2 {
private:
    double topX, topY, side1, side2;

public:
    Triangle2() : topX(0), topY(0), side1(1), side2(1) {}
    Triangle2(double x, double y, double s1, double s2)
        : topX(x), topY(y), side1(s1), side2(s2) {
        if (s1 <= 0 || s2 <= 0) throw invalid_argument("Sides must be positive");
    }

    void input() {
        cout << "Enter top vertex x: ";
        cin >> topX;
        cout << "Enter top vertex y: ";
        cin >> topY;
        cout << "Enter left side length: ";
        cin >> side1;
        cout << "Enter right side length: ";
        cin >> side2;
        if (side1 <= 0 || side2 <= 0) throw invalid_argument("Sides must be positive");
    }

    void display() const {
        cout << "Triangle: top(" << topX << ", " << topY << "), sides=" << side1 << ", " << side2;
    }

    double getBase() const {
        return (side1 + side2) / 2;
    }

    double getArea() const {
        double base = getBase();
        double height = sqrt(side1 * side1 - (base / 2) * (base / 2));
        return 0.5 * base * height;
    }

    double getPerimeter() const {
        return side1 + side2 + getBase();
    }
};

void task7() {
    cout << "\n~~~ TASK 7: Triangles." << endl;

    Triangle2 tri;
    tri.input();
    tri.display();
    cout << endl;
    cout << "Area: " << tri.getArea() << endl;
    cout << "Perimeter: " << tri.getPerimeter() << endl;
}

// task 8
class Time {
private:
    int hours, minutes, seconds;

    void normalize() {
        minutes += seconds / 60;
        seconds %= 60;
        hours += minutes / 60;
        minutes %= 60;
        hours %= 24;
    }

public:
    Time(int h = 0, int m = 0, int s = 0) : hours(h), minutes(m), seconds(s) {
        if (h < 0 || m < 0 || s < 0 || m >= 60 || s >= 60)
            throw invalid_argument("Invalid time values");
        normalize();
    }

    void input() {
        cout << "Enter hours: ";
        cin >> hours;
        cout << "Enter minutes: ";
        cin >> minutes;
        cout << "Enter seconds: ";
        cin >> seconds;
        if (hours < 0 || minutes < 0 || seconds < 0 || minutes >= 60 || seconds >= 60)
            throw invalid_argument("Invalid time values");
        normalize();
    }

    void display() const {
        cout << setfill('0') << setw(2) << hours << ":"
            << setw(2) << minutes << ":" << setw(2) << seconds;
    }

    Time difference(const Time& other) const {
        int totalSeconds1 = hours * 3600 + minutes * 60 + seconds;
        int totalSeconds2 = other.hours * 3600 + other.minutes * 60 + other.seconds;
        int diffSeconds = abs(totalSeconds1 - totalSeconds2);

        return Time(diffSeconds / 3600, (diffSeconds % 3600) / 60, diffSeconds % 60);
    }
};

class Date {
private:
    int year, month, day;
    static Date* instance;

    Date(int y = 2000, int m = 1, int d = 1) : year(y), month(m), day(d) {
        validate();
    }

    void validate() {
        if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
            throw invalid_argument("Invalid date values");
    }

public:
    static Date* getInstance(int y = 2000, int m = 1, int d = 1) {
        if (!instance) {
            instance = new Date(y, m, d);
        }
        return instance;
    }

    void input() {
        cout << "Enter year: ";
        cin >> year;
        cout << "Enter month: ";
        cin >> month;
        cout << "Enter day: ";
        cin >> day;
        validate();
    }

    void display() const {
        cout << setfill('0') << setw(4) << year << "-"
            << setw(2) << month << "-" << setw(2) << day;
    }
};

Date* Date::instance = nullptr;

void task8() {
    cout << "\n~~~ TASK 8: Time and Date Differences." << endl;

    Time t1, t2;
    cout << "Enter first time:\n";
    t1.input();
    cout << "Enter second time:\n";
    t2.input();

    Time diff = t1.difference(t2);
    cout << "Time difference: ";
    diff.display();
    cout << endl;

    Date* date = Date::getInstance();
    date->input();
    cout << "Date: ";
    date->display();
    cout << endl;
}

// task 9
class GameBoard;

class GamePiece {
private:
    string name;
    string game;
    vector<string> moves;

public:
    GamePiece(string n = "", string g = "") : name(n), game(g) {}

    void input() {
        cout << "Enter piece name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter game: ";
        getline(cin, game);

        int moveCount;
        cout << "Enter number of moves: ";
        cin >> moveCount;

        moves.clear();
        for (int i = 0; i < moveCount; i++) {
            string move;
            cout << "Enter move " << (i + 1) << ": ";
            cin >> move;
            moves.push_back(move);
        }
    }

    void display() const {
        cout << "Piece: " << name << " (" << game << ")" << endl;
        cout << "Moves: ";
        for (const auto& move : moves) {
            cout << move << " ";
        }
        cout << endl;
    }
};

class GameBoard {
private:
    int size;
    string gameName;
    vector<GamePiece> pieces;

public:
    GameBoard(int s = 8, string name = "Chess") : size(s), gameName(name) {}

    void input() {
        cout << "Enter board size: ";
        cin >> size;
        cout << "Enter game name: ";
        cin.ignore();
        getline(cin, gameName);

        int pieceCount;
        cout << "Enter number of pieces: ";
        cin >> pieceCount;

        pieces.clear();
        for (int i = 0; i < pieceCount; i++) {
            GamePiece piece;
            piece.input();
            pieces.push_back(piece);
        }
    }

    void display() const {
        cout << "Game Board: " << gameName << " (" << size << "x" << size << ")" << endl;
        cout << "Pieces:" << endl;
        for (const auto& piece : pieces) {
            piece.display();
        }
    }
};

void task9() {
    cout << "\n~~~ TASK 9: Game Board and Pieces." << endl;

    GameBoard board;
    board.input();
    board.display();
}

// task 10
class Currency {
private:
    string name;
    int units;
    int cents;

    void normalize() {
        units += cents / 100;
        cents %= 100;
    }

public:
    Currency(string n = "USD", int u = 0, int c = 0) : name(n), units(u), cents(c) {
        normalize();
    }

    void input() {
        cout << "Enter currency name: ";
        cin >> name;
        cout << "Enter units: ";
        cin >> units;
        cout << "Enter cents: ";
        cin >> cents;
        normalize();
    }

    void display() const {
        cout << units << "." << setfill('0') << setw(2) << cents << " " << name;
    }

    Currency add(const Currency& other) const {
        if (name != other.name) {
            throw invalid_argument("Cannot add different currencies");
        }
        return Currency(name, units + other.units, cents + other.cents);
    }

    Currency subtract(const Currency& other) const {
        if (name != other.name) {
            throw invalid_argument("Cannot subtract different currencies");
        }
        int totalCents1 = units * 100 + cents;
        int totalCents2 = other.units * 100 + other.cents;
        return Currency(name, 0, abs(totalCents1 - totalCents2));
    }

    friend Currency convertCurrency(const Currency& source, double rate, const string& targetName);
};

class Product {
private:
    string name;
    double price;
    Currency currency;
    string unit;

public:
    Product(string n = "", double p = 0, Currency c = Currency(), string u = "pcs")
        : name(n), price(p), currency(c), unit(u) {
    }

    void input() {
        cout << "Enter product name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter price: ";
        cin >> price;
        currency.input();
        cout << "Enter unit: ";
        cin >> unit;
    }

    void display() const {
        cout << name << ": " << price << " ";
        currency.display();
        cout << " per " << unit;
    }
};

Currency convertCurrency(const Currency& source, double rate, const string& targetName) {
    double total = source.units + source.cents / 100.0;
    total *= rate;
    int newUnits = static_cast<int>(total);
    int newCents = static_cast<int>((total - newUnits) * 100);
    return Currency(targetName, newUnits, newCents);
}

void task10() {
    cout << "\n~~~ TASK 10: Currency and Products." << endl;

    Currency curr1, curr2;
    cout << "Enter first currency:\n";
    curr1.input();
    cout << "Enter second currency:\n";
    curr2.input();

    try {
        Currency sum = curr1.add(curr2);
        cout << "Sum: ";
        sum.display();
        cout << endl;
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    Currency converted = convertCurrency(curr1, 0.85, "EUR");
    cout << "Converted: ";
    converted.display();
    cout << endl;
}

// task 11
class Book {
private:
    string title;
    string author;
    int pages;
    int year;

public:
    Book(string t = "", string a = "", int p = 0, int y = 0)
        : title(t), author(a), pages(p), year(y) {
    }

    void input() {
        cout << "Enter title: ";
        cin.ignore();
        getline(cin, title);
        cout << "Enter author: ";
        getline(cin, author);
        cout << "Enter pages: ";
        cin >> pages;
        cout << "Enter year: ";
        cin >> year;
    }

    void display() const {
        cout << "\"" << title << "\" by " << author << " (" << pages << " pages, " << year << ")" << endl;
    }

    string getTitle() const { return title; }
    string getAuthor() const { return author; }

    bool matches(const string& searchAuthor, const string& searchTitle) const {
        return (author.find(searchAuthor) != string::npos) &&
            (title.find(searchTitle) != string::npos);
    }

    void saveToFile(ofstream& file) const {
        file << title << endl;
        file << author << endl;
        file << pages << endl;
        file << year << endl;
    }

    void loadFromFile(ifstream& file) {
        getline(file, title);
        getline(file, author);
        file >> pages;
        file >> year;
        file.ignore();
    }
};

class BookCatalog {
private:
    vector<Book> books;
    string filename;

public:
    BookCatalog(string fname = "books.txt") : filename(fname) {
        loadFromFile();
    }

    void addBook() {
        Book book;
        book.input();
        books.push_back(book);
        saveToFile();
    }

    void searchBooks() {
        string author, title;
        cout << "Enter author to search (or leave empty): ";
        cin.ignore();
        getline(cin, author);
        cout << "Enter title to search (or leave empty): ";
        getline(cin, title);

        bool found = false;
        for (const auto& book : books) {
            if (book.matches(author, title)) {
                book.display();
                found = true;
            }
        }

        if (!found) {
            cout << "No books found matching your criteria." << endl;
        }
    }

    void displayAll() {
        cout << "\n=== BOOK CATALOG ===" << endl;
        for (const auto& book : books) {
            book.display();
        }
    }

    void saveToFile() {
        ofstream file(filename);
        if (file) {
            file << books.size() << endl;
            for (const auto& book : books) {
                book.saveToFile(file);
            }
        }
    }

    void loadFromFile() {
        ifstream file(filename);
        if (file) {
            int count;
            file >> count;
            file.ignore();
            books.clear();
            for (int i = 0; i < count; i++) {
                Book book;
                book.loadFromFile(file);
                books.push_back(book);
            }
        }
    }
};

void createTestBooksFile() {
    ofstream file("books.txt");
    if (file) {
        file << "3" << endl;
        file << "The Great Gatsby" << endl;
        file << "F. Scott Fitzgerald" << endl;
        file << "218" << endl;
        file << "1925" << endl;
        file << "1984" << endl;
        file << "George Orwell" << endl;
        file << "328" << endl;
        file << "1949" << endl;
        file << "To Kill a Mockingbird" << endl;
        file << "Harper Lee" << endl;
        file << "281" << endl;
        file << "1960" << endl;
    }
}

void task11() {
    cout << "\n~~~ TASK 11: Book Catalog." << endl;

    createTestBooksFile();

    BookCatalog catalog;
    int choice;

    do {
        cout << "\n1. Add book\n2. Search books\n3. Display all\n0. Back\nChoice: ";
        cin >> choice;

        switch (choice) {
        case 1: catalog.addBook(); break;
        case 2: catalog.searchBooks(); break;
        case 3: catalog.displayAll(); break;
        }
    } while (choice != 0);
}

// task 12
class Vector {
private:
    int size;
    double* data;

public:
    Vector(int n = 0) : size(n) {
        data = new double[size];
        for (int i = 0; i < size; i++) {
            data[i] = 0.0;
        }
    }

    Vector(int n, const double values[]) : size(n) {
        data = new double[size];
        for (int i = 0; i < size; i++) {
            data[i] = values[i];
        }
    }

    Vector(const Vector& other) : size(other.size) {
        data = new double[size];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    ~Vector() {
        delete[] data;
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new double[size];
            for (int i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    void input() {
        cout << "Enter vector size: ";
        cin >> size;
        delete[] data;
        data = new double[size];
        cout << "Enter " << size << " elements: ";
        for (int i = 0; i < size; i++) {
            cin >> data[i];
        }
    }

    void display() const {
        cout << "[ ";
        for (int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << "]" << endl;
    }

    void setElement(int index, double value) {
        if (index >= 0 && index < size) {
            data[index] = value;
        }
    }

    double getElement(int index) const {
        if (index >= 0 && index < size) {
            return data[index];
        }
        return 0.0;
    }

    int getSize() const { return size; }

    double dotProduct(const Vector& other) const {
        if (size != other.size) {
            throw invalid_argument("Vectors must have same size for dot product");
        }
        double result = 0.0;
        for (int i = 0; i < size; i++) {
            result += data[i] * other.data[i];
        }
        return result;
    }

    Vector crossProduct(const Vector& other) const {
        if (size != 3 || other.size != 3) {
            throw invalid_argument("Cross product only defined for 3D vectors");
        }
        Vector result(3);
        result.data[0] = data[1] * other.data[2] - data[2] * other.data[1];
        result.data[1] = data[2] * other.data[0] - data[0] * other.data[2];
        result.data[2] = data[0] * other.data[1] - data[1] * other.data[0];
        return result;
    }
};

void createTestVectorFile() {
    ofstream file("vector_test.txt");
    if (file) {
        file << "3" << endl;
        file << "1.5 2.5 3.5" << endl;
    }
}

void task12() {
    cout << "\n~~~ TASK 12: Vector Operations." << endl;

    Vector v1, v2;
    cout << "Enter first vector:\n";
    v1.input();
    cout << "Enter second vector:\n";
    v2.input();

    cout << "Vector 1: ";
    v1.display();
    cout << "Vector 2: ";
    v2.display();

    try {
        double dot = v1.dotProduct(v2);
        cout << "Dot product: " << dot << endl;
    }
    catch (const exception& e) {
        cout << "Dot product error: " << e.what() << endl;
    }

    try {
        Vector cross = v1.crossProduct(v2);
        cout << "Cross product: ";
        cross.display();
    }
    catch (const exception& e) {
        cout << "Cross product error: " << e.what() << endl;
    }
}

// task 13
class Vector3 {
private:
    double x, y, z;

public:
    Vector3(double x_val = 0, double y_val = 0, double z_val = 0)
        : x(x_val), y(y_val), z(z_val) {
    }

    void input() {
        cout << "Enter x, y, z: ";
        cin >> x >> y >> z;
    }

    void display() const {
        cout << "(" << x << ", " << y << ", " << z << ")" << endl;
    }

    double norm() const {
        return sqrt(x * x + y * y + z * z);
    }

    Vector3 operator+(const Vector3& other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    Vector3 operator-(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    Vector3 operator*(double scalar) const {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }

    double dot(const Vector3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    Vector3 cross(const Vector3& other) const {
        return Vector3(y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x);
    }

    friend Vector3 operator*(double scalar, const Vector3& vec);
    friend class Matrix3;
};

Vector3 operator*(double scalar, const Vector3& vec) {
    return vec * scalar;
}

class Matrix3 {
private:
    double data[3][3];

public:
    Matrix3() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                data[i][j] = (i == j) ? 1.0 : 0.0;
            }
        }
    }

    Matrix3(const double values[3][3]) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                data[i][j] = values[i][j];
            }
        }
    }

    void input() {
        cout << "Enter 3x3 matrix (row by row):" << endl;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cin >> data[i][j];
            }
        }
    }

    void display() const {
        cout << "Matrix:" << endl;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout << data[i][j] << " ";
            }
            cout << endl;
        }
    }

    double norm() const {
        double sum = 0.0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                sum += data[i][j] * data[i][j];
            }
        }
        return sqrt(sum);
    }

    double det() const {
        return data[0][0] * (data[1][1] * data[2][2] - data[1][2] * data[2][1]) -
            data[0][1] * (data[1][0] * data[2][2] - data[1][2] * data[2][0]) +
            data[0][2] * (data[1][0] * data[2][1] - data[1][1] * data[2][0]);
    }

    Vector3 operator*(const Vector3& vec) const {
        return Vector3(data[0][0] * vec.x + data[0][1] * vec.y + data[0][2] * vec.z,
            data[1][0] * vec.x + data[1][1] * vec.y + data[1][2] * vec.z,
            data[2][0] * vec.x + data[2][1] * vec.y + data[2][2] * vec.z);
    }
};

void task13() {
    cout << "\n~~~ TASK 13: 3D Vectors and Matrices." << endl;

    Vector3 v1, v2;
    cout << "Enter first vector:\n";
    v1.input();
    cout << "Enter second vector:\n";
    v2.input();

    Matrix3 m;
    cout << "Enter matrix:\n";
    m.input();

    cout << "Vector 1: ";
    v1.display();
    cout << "Vector 2: ";
    v2.display();
    m.display();

    cout << "Vector 1 norm: " << v1.norm() << endl;
    cout << "Matrix norm: " << m.norm() << endl;
    cout << "Matrix determinant: " << m.det() << endl;

    Vector3 v3 = m * v1;
    cout << "Matrix * Vector1: ";
    v3.display();
}

// task 14
class TicTacToe {
private:
    char board[3][3];
    char currentPlayer;

public:
    TicTacToe() : currentPlayer('X') {
        initializeBoard();
    }

    void initializeBoard() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board[i][j] = ' ';
            }
        }
    }

    void drawBoard() {
        cout << "\n  0 1 2" << endl;
        for (int i = 0; i < 3; i++) {
            cout << i << " ";
            for (int j = 0; j < 3; j++) {
                cout << board[i][j];
                if (j < 2) cout << "|";
            }
            cout << endl;
            if (i < 2) cout << "  -+-+-" << endl;
        }
        cout << endl;
    }

    bool makeMove(int row, int col) {
        if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != ' ') {
            return false;
        }
        board[row][col] = currentPlayer;
        return true;
    }

    bool checkWin() {
        for (int i = 0; i < 3; i++) {
            if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2])
                return true;
            if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i])
                return true;
        }
        if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
            return true;
        if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
            return true;
        return false;
    }

    bool isBoardFull() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') return false;
            }
        }
        return true;
    }

    void switchPlayer() {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    void playGame() {
        cout << "~ TIC-TAC-TOE ~" << endl;
        cout << "Enter moves as 'row col' (0-2). Enter -1 -1 to quit." << endl;

        while (true) {
            drawBoard();
            cout << "Player " << currentPlayer << "'s turn: ";

            int row, col;
            cin >> row >> col;

            if (row == -1 && col == -1) {
                cout << "Game ended by player." << endl;
                break;
            }

            if (!makeMove(row, col)) {
                cout << "Invalid move! Try again." << endl;
                continue;
            }

            if (checkWin()) {
                drawBoard();
                cout << "Player " << currentPlayer << " wins!" << endl;
                break;
            }

            if (isBoardFull()) {
                drawBoard();
                cout << "It's a draw!" << endl;
                break;
            }

            switchPlayer();
        }
    }
};

void task14() {
    cout << "\n~~~ TASK 14: Tic-Tac-Toe Game." << endl;
    TicTacToe game;
    game.playGame();
}

// task 15
class HotelDate {
private:
    int daysFromReference;

public:
    HotelDate(int days = 0) : daysFromReference(days) {}

    void input() {
        int year, month, day;
        cout << "Enter year, month, day: ";
        cin >> year >> month >> day;
        daysFromReference = (year - 2024) * 365 + (month - 1) * 30 + (day - 1);
    }

    void display() const {
        int years = daysFromReference / 365;
        int months = (daysFromReference % 365) / 30;
        int days = (daysFromReference % 365) % 30;
        cout << (2024 + years) << "-" << (months + 1) << "-" << (days + 1);
    }

    int getDays() const { return daysFromReference; }
    bool operator<(const HotelDate& other) const { return daysFromReference < other.daysFromReference; }
    bool operator<=(const HotelDate& other) const { return daysFromReference <= other.daysFromReference; }
};

class Guest {
private:
    string name;
    HotelDate checkIn;
    HotelDate checkOut;
    int roomNumber;

public:
    void input() {
        cout << "Enter guest name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Check-in date:\n";
        checkIn.input();
        cout << "Check-out date:\n";
        checkOut.input();
        cout << "Room number: ";
        cin >> roomNumber;
    }

    void display() const {
        cout << name << " - Room " << roomNumber << " (";
        checkIn.display();
        cout << " to ";
        checkOut.display();
        cout << ")" << endl;
    }

    bool isStaying(const HotelDate& date) const {
        return checkIn.getDays() <= date.getDays() && date.getDays() <= checkOut.getDays();
    }

    int getRoomNumber() const { return roomNumber; }
    HotelDate getCheckIn() const { return checkIn; }
    HotelDate getCheckOut() const { return checkOut; }
};

class Hotel {
private:
    vector<Guest> guests;
    const int totalRooms = 10;
    const double roomPrice = 100.0;

public:
    void addGuest() {
        Guest guest;
        guest.input();
        guests.push_back(guest);
    }

    void displayFreeRooms(const HotelDate& date) {
        cout << "Free rooms on ";
        date.display();
        cout << ":" << endl;

        vector<bool> occupied(totalRooms + 1, false);
        for (const auto& guest : guests) {
            if (guest.isStaying(date)) {
                occupied[guest.getRoomNumber()] = true;
            }
        }

        for (int i = 1; i <= totalRooms; i++) {
            if (!occupied[i]) {
                cout << "Room " << i << endl;
            }
        }
    }

    void findFreeRoom(const HotelDate& start, const HotelDate& end) {
        cout << "Looking for free room from ";
        start.display();
        cout << " to ";
        end.display();
        cout << ":" << endl;

        for (int room = 1; room <= totalRooms; room++) {
            bool available = true;
            for (const auto& guest : guests) {
                if (guest.getRoomNumber() == room) {
                    bool periodsOverlap = !(end.getDays() < guest.getCheckIn().getDays() ||
                        start.getDays() > guest.getCheckOut().getDays());
                    if (periodsOverlap) {
                        available = false;
                        break;
                    }
                }
            }
            if (available) {
                cout << "Room " << room << " is available" << endl;
                return;
            }
        }
        cout << "No rooms available for this period" << endl;
    }

    void displayAllGuests() {
        cout << "\n~ ALL GUESTS ~" << endl;
        for (const auto& guest : guests) {
            guest.display();
        }
    }
};

void task15() {
    cout << "\n~~~ TASK 15: Hotel Management." << endl;

    Hotel hotel;
    int choice;

    do {
        cout << "\n1. Add guest\n2. Check free rooms\n3. Find free room for period\n4. Display all guests\n0. Back\nChoice: ";
        cin >> choice;

        switch (choice) {
        case 1: hotel.addGuest(); break;
        case 2: {
            HotelDate date;
            cout << "Enter date to check:\n";
            date.input();
            hotel.displayFreeRooms(date);
            break;
        }
        case 3: {
            HotelDate start, end;
            cout << "Enter start date:\n";
            start.input();
            cout << "Enter end date:\n";
            end.input();
            hotel.findFreeRoom(start, end);
            break;
        }
        case 4: hotel.displayAllGuests(); break;
        }
    } while (choice != 0);
}

// task 16
class QuadraticEquation {
private:
    double a, b, c;

public:
    QuadraticEquation(double a_val = 1, double b_val = 0, double c_val = 0)
        : a(a_val), b(b_val), c(c_val) {
    }

    void input() {
        cout << "Enter coefficients a, b, c: ";
        cin >> a >> b >> c;
    }

    void display() const {
        cout << a << "x² + " << b << "x + " << c << " = 0" << endl;
    }

    pair<double, double> findRoots() const {
        double discriminant = b * b - 4 * a * c;
        if (discriminant < 0) {
            throw runtime_error("No real roots");
        }
        double root1 = (-b + sqrt(discriminant)) / (2 * a);
        double root2 = (-b - sqrt(discriminant)) / (2 * a);
        return make_pair(root1, root2);
    }

    double findExtremum() const {
        return -b / (2 * a);
    }

    string getIntervals() const {
        if (a > 0) {
            return "Decreasing: (-∞, " + to_string(findExtremum()) + "), Increasing: (" + to_string(findExtremum()) + ", ∞)";
        }
        else {
            return "Increasing: (-∞, " + to_string(findExtremum()) + "), Decreasing: (" + to_string(findExtremum()) + ", ∞)";
        }
    }
};

void task16() {
    cout << "\n~~~ TASK 16: Quadratic Equations." << endl;

    int n;
    cout << "Enter number of equations: ";
    cin >> n;

    vector<QuadraticEquation> equations;
    for (int i = 0; i < n; i++) {
        QuadraticEquation eq;
        eq.input();
        equations.push_back(eq);
    }

    double minRoot = 1e9, maxRoot = -1e9;

    for (const auto& eq : equations) {
        eq.display();
        try {
            auto roots = eq.findRoots();
            cout << "Roots: " << roots.first << ", " << roots.second << endl;
            minRoot = min(minRoot, min(roots.first, roots.second));
            maxRoot = max(maxRoot, max(roots.first, roots.second));
        }
        catch (const exception& e) {
            cout << e.what() << endl;
        }
        cout << "Extremum: " << eq.findExtremum() << endl;
        cout << "Intervals: " << eq.getIntervals() << endl;
        cout << endl;
    }

    cout << "Smallest root: " << minRoot << endl;
    cout << "Largest root: " << maxRoot << endl;
}

// task 17
class Interval {
private:
    double left, right;
    bool leftIncluded, rightIncluded;

public:
    Interval(double l = 0, double r = 1, bool leftInc = true, bool rightInc = true)
        : left(l), right(r), leftIncluded(leftInc), rightIncluded(rightInc) {
        if (l > r) throw invalid_argument("Left must be <= right");
    }

    void input() {
        cout << "Enter left, right bounds: ";
        cin >> left >> right;
        char leftChar, rightChar;
        cout << "Include left? (y/n): ";
        cin >> leftChar;
        cout << "Include right? (y/n): ";
        cin >> rightChar;
        leftIncluded = (leftChar == 'y' || leftChar == 'Y');
        rightIncluded = (rightChar == 'y' || rightChar == 'Y');
    }

    void display() const {
        cout << (leftIncluded ? "[" : "(") << left << ", " << right << (rightIncluded ? "]" : ")");
    }

    double getLeft() const { return left; }
    double getRight() const { return right; }
};

void task17() {
    cout << "\n~~~ TASK 17: Intervals." << endl;

    int n;
    cout << "Enter number of intervals: ";
    cin >> n;

    vector<Interval> intervals;
    for (int i = 0; i < n; i++) {
        Interval interval;
        interval.input();
        intervals.push_back(interval);
    }

    double minLeft = 1e9, maxRight = -1e9;
    for (const auto& interval : intervals) {
        interval.display();
        cout << endl;
        minLeft = min(minLeft, interval.getLeft());
        maxRight = max(maxRight, interval.getRight());
    }

    cout << "Distance between farthest ends: " << (maxRight - minLeft) << endl;
}

// task 18
class TimedPoint {
private:
    double x, y;
    double vx, vy;
    double ax, ay;

public:
    TimedPoint(double x_val = 0, double y_val = 0, double vx_val = 0, double vy_val = 0,
        double ax_val = 0, double ay_val = 0)
        : x(x_val), y(y_val), vx(vx_val), vy(vy_val), ax(ax_val), ay(ay_val) {
    }

    void input() {
        cout << "Enter initial x, y: ";
        cin >> x >> y;
        cout << "Enter velocity vx, vy: ";
        cin >> vx >> vy;
        cout << "Enter acceleration ax, ay: ";
        cin >> ax >> ay;
    }

    void display() const {
        cout << "Position: (" << x << ", " << y << "), ";
        cout << "Velocity: (" << vx << ", " << vy << "), ";
        cout << "Acceleration: (" << ax << ", " << ay << ")" << endl;
    }

    pair<double, double> getPositionAtTime(double t) const {
        double xt = x + vx * t + 0.5 * ax * t * t;
        double yt = y + vy * t + 0.5 * ay * t * t;
        return make_pair(xt, yt);
    }

    pair<double, double> getVelocityAtTime(double t) const {
        double vxt = vx + ax * t;
        double vyt = vy + ay * t;
        return make_pair(vxt, vyt);
    }

    double distanceTo(const TimedPoint& other, double t) const {
        auto pos1 = getPositionAtTime(t);
        auto pos2 = other.getPositionAtTime(t);
        return sqrt(pow(pos1.first - pos2.first, 2) + pow(pos1.second - pos2.second, 2));
    }
};

void task18() {
    cout << "\n~~~ TASK 18: Timed Points." << endl;

    TimedPoint p1, p2;
    cout << "Enter first point:\n";
    p1.input();
    cout << "Enter second point:\n";
    p2.input();

    double t;
    cout << "Enter time t: ";
    cin >> t;

    cout << "At time " << t << ":" << endl;
    cout << "Point 1: ";
    auto pos1 = p1.getPositionAtTime(t);
    auto vel1 = p1.getVelocityAtTime(t);
    cout << "Position (" << pos1.first << ", " << pos1.second << "), ";
    cout << "Velocity (" << vel1.first << ", " << vel1.second << ")" << endl;

    cout << "Point 2: ";
    auto pos2 = p2.getPositionAtTime(t);
    auto vel2 = p2.getVelocityAtTime(t);
    cout << "Position (" << pos2.first << ", " << pos2.second << "), ";
    cout << "Velocity (" << vel2.first << ", " << vel2.second << ")" << endl;

    cout << "Distance between points: " << p1.distanceTo(p2, t) << endl;
}

// main menu
void displayMenu() {
    cout << "\n~~~~~" << endl;
    cout << "Main menu" << endl;
    cout << "~~~~~" << endl;
    cout << "4. Points, Segments, Triangles" << endl;
    cout << "5. Circles" << endl;
    cout << "6. Rectangles" << endl;
    cout << "7. Triangles" << endl;
    cout << "8. Time and Date Differences" << endl;
    cout << "9. Game Board and Pieces" << endl;
    cout << "10. Currency and Products" << endl;
    cout << "11. Book Catalog" << endl;
    cout << "12. Vector Operations" << endl;
    cout << "13. 3D Vectors and Matrices" << endl;
    cout << "14. Tic-Tac-Toe Game" << endl;
    cout << "15. Hotel Management" << endl;
    cout << "16. Quadratic Equations" << endl;
    cout << "17. Intervals" << endl;
    cout << "18. Timed Points" << endl;
    cout << "0. Exit" << endl;
    cout << "~~~~~" << endl;
    cout << "Enter your choice (4-18): ";
}

int main() {
    int choice;

    // Create test files
    createTestBooksFile();
    createTestVectorFile();

    do {
        displayMenu();
        cin >> choice;

        try {
            switch (choice) {
            case 4: task4(); break;
            case 5: task5(); break;
            case 6: task6(); break;
            case 7: task7(); break;
            case 8: task8(); break;
            case 9: task9(); break;
            case 10: task10(); break;
            case 11: task11(); break;
            case 12: task12(); break;
            case 13: task13(); break;
            case 14: task14(); break;
            case 15: task15(); break;
            case 16: task16(); break;
            case 17: task17(); break;
            case 18: task18(); break;
            case 0: cout << "Bye!" << endl; break;
            default: cout << "Invalid choice!" << endl; break;
            }
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }

        if (choice != 0) {
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }

    } while (choice != 0);

    return 0;
}