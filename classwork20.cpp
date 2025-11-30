#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <list>
#include <limits>

using namespace std;

// task 1 (Chapter 20.1)
void task1() {
    cout << "~~~ 20.1: queue time ~~~\n";

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

// task 2 (Chapter 20.3)
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
                if (!first) {
                    if (coeffs[i] > T(0)) cout << " + ";
                    else cout << " - ";
                }

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

void task2() {
    cout << "\n~~~ 20.3 : polynomial ~~~\n";

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

// task 3 (Chapter 21.2)
void task3() {
    cout << "\n~~~ 21.2 : list partition by x ~~~\n";

    list<int> lst;
    int n, x, value;

    cout << "Enter number of elements in list: ";
    cin >> n;

    cout << "Enter " << n << " integers:\n";
    for (int i = 0; i < n; i++) {
        cin >> value;
        lst.push_back(value);
    }

    cout << "Enter number X: ";
    cin >> x;

    cout << "Original list: ";
    for (auto it = lst.begin(); it != lst.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;

    auto it = lst.begin();
    int count = 0;

    while (count < n) {
        if (*it > x) {
            int temp = *it;
            it = lst.erase(it);
            lst.push_back(temp);
        }
        else {
            it++;
        }
        count++;
    }

    cout << "Partitioned list: ";
    for (auto it = lst.begin(); it != lst.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
}

// task 4 (Chapter 21.3)

double sumOfKLargest(const vector<double>& vec, int k) {
    if (k <= 0 || k > vec.size()) {
        return 0.0;
    }

    vector<double> temp = vec;
    sort(temp.begin(), temp.end(), greater<double>());

    double sum = 0.0;
    for (int i = 0; i < k; i++) {
        sum += temp[i];
    }

    return sum;
}

vector<double> kSmallestNumbers(const vector<double>& vec, int k) {
    vector<double> result;

    if (k <= 0 || k > vec.size()) {
        return result;
    }

    vector<double> temp = vec;
    sort(temp.begin(), temp.end());

    for (int i = 0; i < k; i++) {
        result.push_back(temp[i]);
    }

    return result;
}

void task4() {
    cout << "\n~~~ 21.3 : k largest/smallest ~~~\n";

    int n, k;
    cout << "Enter vector size: ";
    cin >> n;

    vector<double> vec(n);
    cout << "Enter " << n << " numbers:\n";
    for (int i = 0; i < n; i++) {
        cin >> vec[i];
    }

    cout << "Enter k: ";
    cin >> k;

    double sum_largest = sumOfKLargest(vec, k);
    cout << "Sum of " << k << " largest numbers: " << sum_largest << endl;

    vector<double> smallest = kSmallestNumbers(vec, k);
    cout << k << " smallest numbers: ";
    for (double num : smallest) {
        cout << num << " ";
    }
    cout << endl;
}

void testTask1() {
    cout << "\n~ Test task 1 ~\n";

    cout << "Test 1 - Input: 4 customers, times: 5.5, 3.2, 7.1, 2.8\n";
    vector<double> times = { 5.5, 3.2, 7.1, 2.8 };
    vector<double> queue_times(4);

    queue_times[0] = times[0];
    for (int i = 1; i < 4; i++) {
        queue_times[i] = queue_times[i - 1] + times[i];
    }

    cout << "Expected queue times:\n";
    cout << "Customer 1: 5.5\n";
    cout << "Customer 2: 8.7\n";
    cout << "Customer 3: 15.8\n";
    cout << "Customer 4: 18.6\n";
    cout << "Min service: Customer 4 (2.8)\n";
    cout << "Max queue: Customer 4 (18.6)\n";
}

void testTask2() {
    cout << "\n~ Test task 2 ~\n";

    cout << "Test with integers:\n";
    cout << "P1: x^2 - 3x + 2\n";
    cout << "P2: 2x + 1\n";
    cout << "x = 2\n\n";

    Polynomial<int> p1(vector<int>{2, -3, 1});
    Polynomial<int> p2(vector<int>{1, 2});

    cout << "P1 = "; p1.output(); cout << endl;
    cout << "P2 = "; p2.output(); cout << endl;

    Polynomial<int> sum = p1 + p2;
    cout << "Sum = "; sum.output(); cout << endl;

    Polynomial<int> product = p1 * p2;
    cout << "Product = "; product.output(); cout << endl;

    cout << "P1(2) = " << p1.evaluate(2) << " (expected: 0)\n";
    cout << "P2(2) = " << p2.evaluate(2) << " (expected: 5)\n";
}

void testTask3() {
    cout << "\n~ Test task 3 ~\n";

    list<int> test1 = { 5, 2, 8, 1, 9, 3 };
    int x1 = 4;

    cout << "Test 1 - List: 5 2 8 1 9 3, X = 4\n";
    cout << "Expected: 2 1 3 5 8 9\n";

    auto it = test1.begin();
    int count = 0;
    int n = test1.size();

    while (count < n) {
        if (*it > x1) {
            int temp = *it;
            it = test1.erase(it);
            test1.push_back(temp);
        }
        else {
            it++;
        }
        count++;
    }

    cout << "Actual:   ";
    for (auto num : test1) cout << num << " ";
    cout << endl;
}

void testTask4() {
    cout << "\n~ Test task 4 ~\n";

    vector<double> test1 = { 7.5, 2.1, 9.8, 1.2, 5.4 };
    int k = 3;

    cout << "Test 1 - Vector: 7.5 2.1 9.8 1.2 5.4, k = 3\n";

    double sum = sumOfKLargest(test1, k);
    vector<double> smallest = kSmallestNumbers(test1, k);

    cout << "Sum of 3 largest: " << sum << " (expected: 22.7)\n";
    cout << "3 smallest numbers: ";
    for (double num : smallest) cout << num << " ";
    cout << "(expected: 1.2 2.1 5.4)\n";
}

int main() {
    int choice;

    while (true) {
        cout << "\n~~~ MAIN MENU ~~~\n";
        cout << "1. Task 1 - Queue Time (20.1)\n";
        cout << "2. Task 2 - Polynomial (20.3)\n";
        cout << "3. Task 3 - List Partition (21.2)\n";
        cout << "4. Task 4 - K Largest/Smallest (21.3)\n";
        cout << "5. Test Task 1\n";
        cout << "6. Test Task 2\n";
        cout << "7. Test Task 3\n";
        cout << "8. Test Task 4\n";
        cout << "9. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        switch (choice) {
        case 1: task1(); break;
        case 2: task2(); break;
        case 3: task3(); break;
        case 4: task4(); break;
        case 5: testTask1(); break;
        case 6: testTask2(); break;
        case 7: testTask3(); break;
        case 8: testTask4(); break;
        case 9: return 0;
        default: cout << "Invalid choice!\n";
        }
    }

    return 0;
}