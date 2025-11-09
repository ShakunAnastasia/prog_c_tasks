#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdexcept>

using namespace std;

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

class Rational {
private:
    int numerator;
    int denominator;

    void reduce() {
        if (denominator == 0) {
            throw runtime_error("Denominator cannot be zero");
        }

        int gcd_val = gcd(abs(numerator), abs(denominator));
        numerator /= gcd_val;
        denominator /= gcd_val;

        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

public:
    Rational() : numerator(1), denominator(1) {} 

    Rational(int num, int den) : numerator(num), denominator(den) { 
        if (den == 0) {
            throw invalid_argument("Denominator cannot be zero");
        }
        reduce();
    }

    int getNumerator() const { return numerator; }
    int getDenominator() const { return denominator; }

    void setNumerator(int num) {
        numerator = num;
        reduce();
    }

    void setDenominator(int den) {
        if (den == 0) {
            throw invalid_argument("Denominator cannot be zero");
        }
        denominator = den;
        reduce();
    }

    void inputFromTerminal() {
        cout << "Enter numerator: ";
        cin >> numerator;

        int den;
        do {
            cout << "Enter denominator (non-zero): ";
            cin >> den;
            if (den == 0) {
                cout << "Error: Denominator cannot be zero. Please try again." << endl;
            }
        } while (den == 0);

        denominator = den;
        reduce();
    }

    void outputToTerminal() const {
        if (denominator == 1) {
            cout << numerator;
        }
        else {
            cout << numerator << "/" << denominator;
        }
    }

    Rational add(const Rational& other) const {
        int new_num = numerator * other.denominator + other.numerator * denominator;
        int new_den = denominator * other.denominator;
        return Rational(new_num, new_den);
    }

    Rational multiply(const Rational& other) const {
        int new_num = numerator * other.numerator;
        int new_den = denominator * other.denominator;
        return Rational(new_num, new_den);
    }

    Rational operator+(const Rational& other) const {
        return add(other);
    }

    Rational operator-(const Rational& other) const {
        int new_num = numerator * other.denominator - other.numerator * denominator;
        int new_den = denominator * other.denominator;
        return Rational(new_num, new_den);
    }

    Rational operator*(const Rational& other) const {
        return multiply(other);
    }

    Rational operator/(const Rational& other) const {
        if (other.numerator == 0) {
            throw runtime_error("Division by zero");
        }
        int new_num = numerator * other.denominator;
        int new_den = denominator * other.numerator;
        return Rational(new_num, new_den);
    }

    bool operator==(const Rational& other) const {
        return numerator * other.denominator == other.numerator * denominator;
    }

    bool operator!=(const Rational& other) const {
        return !(*this == other);
    }

    bool operator<(const Rational& other) const {
        return numerator * other.denominator < other.numerator * denominator;
    }

    bool operator>(const Rational& other) const {
        return numerator * other.denominator > other.numerator * denominator;
    }

    bool operator<=(const Rational& other) const {
        return *this < other || *this == other;
    }

    bool operator>=(const Rational& other) const {
        return *this > other || *this == other;
    }

    double toDouble() const {
        return static_cast<double>(numerator) / denominator;
    }

    friend ostream& operator<<(ostream& os, const Rational& rat) {
        if (rat.denominator == 1) {
            os << rat.numerator;
        }
        else {
            os << rat.numerator << "/" << rat.denominator;
        }
        return os;
    }

    friend istream& operator>>(istream& is, Rational& rat) {
        int num, den;
        char slash;

        is >> num;
        if (is.peek() == '/') {
            is >> slash >> den;
            if (den == 0) {
                is.setstate(ios::failbit);
                return is;
            }
        }
        else {
            den = 1;
        }

        rat = Rational(num, den);
        return is;
    }
};

Rational findSmallestRational(const Rational arr[], int size) {
    if (size <= 0) {
        throw invalid_argument("Array size must be positive");
    }

    Rational smallest = arr[0];
    for (int i = 1; i < size; ++i) {
        if (arr[i] < smallest) {
            smallest = arr[i];
        }
    }
    return smallest;
}

double calculatePiSeries(double precision) {
    double sum = 0.0;
    double term;
    int n = 1;
    int sign = 1;

    do {
        term = sign * (1.0 / (n * n));
        sum += term;
        sign = -sign;
        n++;
    } while (abs(term) > precision);

    return sum;
}

void demonstrateRationalClass() {
    cout << "Demonstrating rational class" << endl;

    Rational r1; 
    Rational r2(3, 4);
    Rational r3(6, 8); 

    cout << "r1 (default): " << r1 << endl;
    cout << "r2 (3/4): " << r2 << endl;
    cout << "r3 (6/8 reduced): " << r3 << endl;

    Rational sum = r2 + r3;
    Rational product = r2 * r3;

    cout << "r2 + r3 = " << sum << endl;
    cout << "r2 * r3 = " << product << endl;

    cout << "r2 == r3: " << (r2 == r3 ? "true" : "false") << endl;
    cout << "r2 < r1: " << (r2 < r1 ? "true" : "false") << endl;
}

void findSmallestInArray() {
    cout << "\nFinding smallest rational in array" << endl;

    Rational numbers[] = {
        Rational(1, 2),
        Rational(3, 4),
        Rational(1, 3),
        Rational(2, 5),
        Rational(5, 6)
    };

    int size = sizeof(numbers) / sizeof(numbers[0]);

    cout << "Array: ";
    for (int i = 0; i < size; ++i) {
        cout << numbers[i];
        if (i < size - 1) cout << ", ";
    }
    cout << endl;

    Rational smallest = findSmallestRational(numbers, size);
    cout << "Smallest rational: " << smallest << " (" << smallest.toDouble() << ")" << endl;
}

void calculatePiSeriesDemo() {
    cout << "\nCalculating pi series" << endl;

    double precision = 0.01;
    double seriesSum = calculatePiSeries(precision);
    double pi_squared = 3.14159265358979323846 * 3.14159265358979323846;
    double expected = pi_squared / 12.0;

    cout << fixed << setprecision(6);
    cout << "Series sum with precision " << precision << ": " << seriesSum << endl;
    cout << "Expected value (π²/12): " << expected << endl;
    cout << "Difference: " << abs(seriesSum - expected) << endl;
    cout << "Series converges to expected value: "
        << (abs(seriesSum - expected) < precision ? "Yes" : "No") << endl;
}

int main() {
    demonstrateRationalClass();
    findSmallestInArray();
    calculatePiSeriesDemo();

    return 0;
}