#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

void task1() {
    cout << "~~~ TASK 1: queue time ~~~\n";

    int n;
    cout << "Enter number of customers: ";
    cin >> n;

    vector<double> t(n), c(n);

    cout << "Enter service times:\n";
    for (int i = 0; i < n; i++) {
        cout << "t[" << i + 1 << "] = ";
        cin >> t[i];
    }

    c[0] = t[0];
    for (int i = 1; i < n; i++) {
        c[i] = c[i - 1] + t[i];
    }

    int min_index = 0;
    int max_index = 0;

    for (int i = 1; i < n; i++) {
        if (t[i] < t[min_index]) min_index = i;
        if (c[i] > c[max_index]) max_index = i;
    }

    cout << "\nResults:\n";
    for (int i = 0; i < n; i++) {
        cout << "Customer " << i + 1 << " queue time: " << c[i] << endl;
    }

    cout << "\nMin service time: Customer " << min_index + 1 << " (" << t[min_index] << ")\n";
    cout << "Max queue time: Customer " << max_index + 1 << " (" << c[max_index] << ")\n";
}

void task2() {
    cout << "\n~~~ TASK 2: vector norms ~~~\n";

    int d, n;
    cout << "Enter vector dimension: ";
    cin >> d;
    cout << "Enter number of vectors: ";
    cin >> n;

    vector<vector<double>> vectors(n, vector<double>(d));
    double total_sum = 0;

    for (int i = 0; i < n; i++) {
        cout << "Vector " << i + 1 << ":\n";
        for (int j = 0; j < d; j++) {
            cout << "Coordinate " << j + 1 << ": ";
            cin >> vectors[i][j];
        }
    }

    cout << "\nNorms:\n";
    for (int i = 0; i < n; i++) {
        double norm = 0;
        for (int j = 0; j < d; j++) {
            norm += vectors[i][j] * vectors[i][j];
        }
        norm = sqrt(norm);
        total_sum += norm;
        cout << "Vector " << i + 1 << " norm: " << norm << endl;
    }

    cout << "Sum of norms: " << total_sum << endl;
}

template<typename T>
class Polynomial {
private:
    vector<T> coeffs;

public:
    Polynomial() {}

    Polynomial(const vector<T>& c) : coeffs(c) {}

    void input() {
        int degree;
        cout << "Enter polynomial degree: ";
        cin >> degree;

        coeffs.resize(degree + 1);
        cout << "Enter coefficients from highest to lowest degree:\n";
        for (int i = degree; i >= 0; i--) {
            cout << "x^" << i << ": ";
            cin >> coeffs[i];
        }
    }

    void output() {
        if (coeffs.empty()) {
            cout << "0";
            return;
        }

        bool first = true;
        for (int i = coeffs.size() - 1; i >= 0; i--) {
            if (coeffs[i] != T(0)) {
                if (!first && coeffs[i] > T(0)) cout << " + ";
                if (coeffs[i] < T(0)) cout << " - ";

                T val = (coeffs[i] < T(0)) ? -coeffs[i] : coeffs[i];

                if (val != T(1) || i == 0) cout << val;
                if (i > 0) cout << "x";
                if (i > 1) cout << "^" << i;

                first = false;
            }
        }
        if (first) cout << "0";
    }

    Polynomial<T> operator+(const Polynomial<T>& other) {
        int max_size = max(coeffs.size(), other.coeffs.size());
        vector<T> result(max_size, T(0));

        for (int i = 0; i < coeffs.size(); i++) result[i] += coeffs[i];
        for (int i = 0; i < other.coeffs.size(); i++) result[i] += other.coeffs[i];

        return Polynomial<T>(result);
    }

    Polynomial<T> operator*(const Polynomial<T>& other) {
        int size = coeffs.size() + other.coeffs.size() - 1;
        vector<T> result(size, T(0));

        for (int i = 0; i < coeffs.size(); i++) {
            for (int j = 0; j < other.coeffs.size(); j++) {
                result[i + j] += coeffs[i] * other.coeffs[j];
            }
        }

        return Polynomial<T>(result);
    }

    T evaluate(T x) {
        T result = T(0);
        T power = T(1);

        for (int i = 0; i < coeffs.size(); i++) {
            result += coeffs[i] * power;
            power *= x;
        }

        return result;
    }
};

void task3() {
    cout << "\n~~~ TASK 3: polynomial ~~~\n";

    int type;
    cout << "Choose type: 1-int, 2-double: ";
    cin >> type;

    if (type == 1) {
        Polynomial<int> p1, p2;

        cout << "Polynomial 1:\n";
        p1.input();
        cout << "Polynomial 2:\n";
        p2.input();

        cout << "\nP1 = "; p1.output(); cout << endl;
        cout << "P2 = "; p2.output(); cout << endl;

        Polynomial<int> sum = p1 + p2;
        cout << "Sum = "; sum.output(); cout << endl;

        Polynomial<int> product = p1 * p2;
        cout << "Product = "; product.output(); cout << endl;

        int x;
        cout << "Enter x for evaluation: ";
        cin >> x;
        cout << "P1(" << x << ") = " << p1.evaluate(x) << endl;
        cout << "P2(" << x << ") = " << p2.evaluate(x) << endl;

    }
    else if (type == 2) {
        Polynomial<double> p1, p2;

        cout << "Polynomial 1:\n";
        p1.input();
        cout << "Polynomial 2:\n";
        p2.input();

        cout << "\nP1 = "; p1.output(); cout << endl;
        cout << "P2 = "; p2.output(); cout << endl;

        Polynomial<double> sum = p1 + p2;
        cout << "Sum = "; sum.output(); cout << endl;

        Polynomial<double> product = p1 * p2;
        cout << "Product = "; product.output(); cout << endl;

        double x;
        cout << "Enter x for evaluation: ";
        cin >> x;
        cout << "P1(" << x << ") = " << p1.evaluate(x) << endl;
        cout << "P2(" << x << ") = " << p2.evaluate(x) << endl;
    }
}

void task4() {
    cout << "\n~~~ TASK 4: matrix sort ~~~\n";

    int n, m;
    cout << "Enter rows and columns (n m): ";
    cin >> n >> m;

    vector<vector<double>> matrix(n, vector<double>(m));

    cout << "Enter matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> matrix[i][j];
        }
    }

    vector<pair<double, vector<double>>> rows;
    for (int i = 0; i < n; i++) {
        double max_val = *max_element(matrix[i].begin(), matrix[i].end());
        rows.push_back({ max_val, matrix[i] });
    }

    sort(rows.begin(), rows.end(), [](auto& a, auto& b) {
        return a.first > b.first;
        });

    cout << "\nSorted matrix:\n";
    for (auto& row : rows) {
        for (double val : row.second) {
            cout << setw(8) << val << " ";
        }
        cout << endl;
    }
}

int main() {
    while (true) {
        cout << "\n~~~ MAIN MENU ~~~\n";
        cout << "1. Queue time\n";
        cout << "2. Vector norms\n";
        cout << "3. Polynomial\n";
        cout << "4. Matrix sort\n";
        cout << "5. Exit\n";
        cout << "Choose: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1: task1(); break;
        case 2: task2(); break;
        case 3: task3(); break;
        case 4: task4(); break;
        case 5: return 0;
        default: cout << "Invalid choice!\n";
        }
    }

    return 0;
}