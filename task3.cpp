#include <iostream>
#include <fstream>
#include <memory>
#include <stdexcept>

using namespace std;

class Polynomial {
private:
    int degree;
    double* coefficients;

public:
    Polynomial(int n = 0) : degree(n) {
        if (n < 0) {
            throw invalid_argument("Degree cannot be negative");
        }
        coefficients = new double[degree + 1]; 
        for (int i = 0; i <= degree; i++) {
            coefficients[i] = 0.0;
        }
    }

    Polynomial(int n, const double coeffs[]) : degree(n) {
        coefficients = new double[degree + 1];
        for (int i = 0; i <= degree; i++) {
            coefficients[i] = coeffs[i];
        }
    }

    Polynomial(const Polynomial& other) : degree(other.degree) {
        coefficients = new double[degree + 1];
        for (int i = 0; i <= degree; i++) {
            coefficients[i] = other.coefficients[i];
        }
    }

    ~Polynomial() {
        delete[] coefficients;
    }

    void initialize(const double coeffs[]) {
        for (int i = 0; i <= degree; i++) {
            coefficients[i] = coeffs[i];
        }
    }

    void setCoefficient(int index, double value) {
        if (index < 0 || index > degree) {
            throw out_of_range("Index out of range");
        }
        coefficients[index] = value;
    }

    double getCoefficient(int index) const {
        if (index < 0 || index > degree) {
            throw out_of_range("Index out of range");
        }
        return coefficients[index];
    }

    int getDegree() const {
        return degree;
    }

    void display() const {
        bool firstTerm = true;

        for (int i = degree; i >= 0; i--) {
            if (coefficients[i] != 0.0) {
                if (!firstTerm && coefficients[i] > 0) {
                    cout << " + ";
                }
                else if (coefficients[i] < 0) {
                    cout << " - ";
                }

                double absValue = abs(coefficients[i]);

                if (i == 0) {
                    cout << absValue;
                }
                else if (i == 1) {
                    if (absValue != 1.0) {
                        cout << absValue << "*x";
                    }
                    else {
                        cout << "x";
                    }
                }
                else {
                    if (absValue != 1.0) {
                        cout << absValue << "*x^" << i;
                    }
                    else {
                        cout << "x^" << i;
                    }
                }

                firstTerm = false;
            }
        }

        if (firstTerm) {
            cout << "0";
        }
        cout << endl;
    }

    Polynomial& operator=(const Polynomial& other) {
        if (this != &other) {
            delete[] coefficients;

            degree = other.degree;
            coefficients = new double[degree + 1];

            for (int i = 0; i <= degree; i++) {
                coefficients[i] = other.coefficients[i];
            }
        }
        return *this;
    }

    friend ostream& operator<<(ostream& os, const Polynomial& poly);
    friend istream& operator>>(istream& is, Polynomial& poly);

    friend void writeToBinaryFile(const Polynomial& poly, const string& filename);
    friend Polynomial readFromBinaryFile(const string& filename);
};

ostream& operator<<(ostream& os, const Polynomial& poly) {
    bool firstTerm = true;

    for (int i = poly.degree; i >= 0; i--) {
        if (poly.coefficients[i] != 0.0) {
            if (!firstTerm && poly.coefficients[i] > 0) {
                os << " + ";
            }
            else if (poly.coefficients[i] < 0) {
                os << " - ";
            }

            double absValue = abs(poly.coefficients[i]);

            if (i == 0) {
                os << absValue;
            }
            else if (i == 1) {
                if (absValue != 1.0) {
                    os << absValue << "*x";
                }
                else {
                    os << "x";
                }
            }
            else {
                if (absValue != 1.0) {
                    os << absValue << "*x^" << i;
                }
                else {
                    os << "x^" << i;
                }
            }

            firstTerm = false;
        }
    }

    if (firstTerm) {
        os << "0";
    }
    return os;
}

istream& operator>>(istream& is, Polynomial& poly) {
    cout << "Enter degree of polynomial: ";
    is >> poly.degree;

    if (poly.degree < 0) {
        is.setstate(ios::failbit);
        return is;
    }

    delete[] poly.coefficients;
    poly.coefficients = new double[poly.degree + 1];

    cout << "Enter coefficients from x^0 to x^" << poly.degree << ":" << endl;
    for (int i = 0; i <= poly.degree; i++) {
        cout << "Coefficient for x^" << i << ": ";
        is >> poly.coefficients[i];
    }

    return is;
}

void writeToBinaryFile(const Polynomial& poly, const string& filename) {
    ofstream file(filename, ios::binary);
    if (!file) {
        throw runtime_error("Cannot open file for writing");
    }

    file.write(reinterpret_cast<const char*>(&poly.degree), sizeof(poly.degree));

    file.write(reinterpret_cast<const char*>(poly.coefficients),
        (poly.degree + 1) * sizeof(double));

    file.close();
}

Polynomial readFromBinaryFile(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        throw runtime_error("Cannot open file for reading");
    }

    int degree;
    file.read(reinterpret_cast<char*>(&degree), sizeof(degree));

    Polynomial poly(degree);

    file.read(reinterpret_cast<char*>(poly.coefficients),
        (degree + 1) * sizeof(double));

    file.close();
    return poly;
}

void demonstrateConstructors() {
    cout << "Demonstrating constructors" << endl;

    Polynomial p1;
    cout << "Default polynomial: " << p1 << endl;

    Polynomial p2(3);
    cout << "Polynomial with degree 3 (all zeros): " << p2 << endl;

    double coeffs[] = { 1, 2, 3, 4 };
    Polynomial p3(3, coeffs);
    cout << "Polynomial with initial values: " << p3 << endl;
}

void demonstrateMethods() {
    cout << "\nDemonstrating methods" << endl;

    Polynomial poly(3);

    poly.setCoefficient(0, 5);
    poly.setCoefficient(1, -2);
    poly.setCoefficient(2, 3);
    poly.setCoefficient(3, 1);

    cout << "Polynomial after setting coefficients: " << poly << endl;

    cout << "Coefficient for x^2: " << poly.getCoefficient(2) << endl;
    cout << "Degree: " << poly.getDegree() << endl;
}

void demonstrateCopyAndAssignment() {
    cout << "\nDemonstrating copy and assignment" << endl;

    double coeffs[] = { 2, -1, 0, 3 };
    Polynomial original(3, coeffs);
    cout << "Original: " << original << endl;

    Polynomial copy = original;
    cout << "Copy: " << copy << endl;

    Polynomial assigned;
    assigned = original;
    cout << "Assigned: " << assigned << endl;
}

void demonstrateFileIO() {
    cout << "\nDemonstrating binary file i/o" << endl;

    double coeffs[] = { 1, -2, 0, 4, -1 };
    Polynomial poly(4, coeffs);
    cout << "Original polynomial: " << poly << endl;

    writeToBinaryFile(poly, "polynomial.bin");
    cout << "Polynomial written to file 'polynomial.bin'" << endl;

    Polynomial readPoly = readFromBinaryFile("polynomial.bin");
    cout << "Polynomial read from file: " << readPoly << endl;
}

void interactiveDemo() {
    cout << "\nInteractive demonstration" << endl;

    Polynomial poly;
    cin >> poly;

    cout << "Your polynomial: " << poly << endl;

    int index;
    double value;
    cout << "Enter index to modify: ";
    cin >> index;
    cout << "Enter new value: ";
    cin >> value;

    try {
        poly.setCoefficient(index, value);
        cout << "Modified polynomial: " << poly << endl;
    }
    catch (const out_of_range& e) {
        cout << "Error: " << e.what() << endl;
    }
}

int main() {
    try {
        demonstrateConstructors();
        demonstrateMethods();
        demonstrateCopyAndAssignment();
        demonstrateFileIO();
        interactiveDemo();
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}