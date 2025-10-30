#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <limits>

using namespace std;

void displayMenu() {
    cout << "~TASK SELECTION~" << endl;
    cout << "1. Task 1: Power calculation" << endl;
    cout << "2. Task 2: Sum of 10-digit numbers" << endl;
    cout << "3. Task 3: Square root table" << endl;
    cout << "4. Task 4: Array power calculation" << endl;
    cout << "5. Task 5: Reverse square roots" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter your choice (0-5): ";
}

void task1() {
    cout << "\nTask 1: Power calculation" << endl;

    double x, y;
    cout << "Enter real number x: ";
    cin >> x;
    cout << "Enter real number y: ";
    cin >> y;

    double result = pow(x, y);

    cout << "Decimal format: " << fixed << result << endl;

    cout << "Scientific format: " << scientific << result << endl;

    cout.unsetf(ios_base::floatfield);
}

void task2() {
    cout << "\nTask 2: Sum of 10-digit numbers" << endl;

    string input;
    cout << "Enter digits (multiple of 10): ";
    cin >> input;

    int totalDigits = input.length();
    if (totalDigits % 10 != 0) {
        cout << "Error: Number of digits must be multiple of 10!" << endl;
        return;
    }

    int n = totalDigits / 10;
    vector<unsigned long long> numbers(n);

    for (int i = 0; i < n; ++i) {
        string digitStr = input.substr(i * 10, 10);
        numbers[i] = stoull(digitStr);
    }

    unsigned long long sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += numbers[i];
    }

    cout << "Sum of " << n << " numbers: " << sum << endl;
}

void task3() {
    cout << "\nTask 3: Square root table" << endl;

    int n;
    cout << "Enter natural number n: ";
    cin >> n;

    if (n <= 0) {
        cout << "Error: n must be positive!" << endl;
        return;
    }

    int maxNumWidth = to_string(n).length();
    int maxRootWidth = to_string((int)sqrt(n)).length() + 3;

    for (int i = 1; i <= n; ++i) {
        cout << setw(maxRootWidth) << i;
        if (i < n) cout << " ";
    }
    cout << endl;

    for (int i = 1; i <= n; ++i) {
        double root = sqrt(i);

        if (root == floor(root)) {
            cout << setw(maxRootWidth) << fixed << setprecision(0) << root;
        }
        else {
            cout << setw(maxRootWidth) << fixed << setprecision(2) << root;
        }

        if (i < n) cout << " ";
    }
    cout << endl;
}

void task4() {
    cout << "\nTask 4: Array power calculation" << endl;

    int n;
    cout << "Enter natural number n: ";
    cin >> n;

    if (n <= 0) {
        cout << "Error: n must be positive!" << endl;
        return;
    }

    vector<int> m(n);
    cout << "Enter " << n << " integers: ";
    for (int i = 0; i < n; ++i) {
        cin >> m[i];
    }

    string filename;
    cout << "Enter input filename: ";
    cin >> filename;

    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Error: Cannot open file " << filename << endl;
        return;
    }

    vector<double> x(n);
    for (int i = 0; i < n; ++i) {
        if (!(inputFile >> x[i])) {
            cout << "Error: File doesn't contain enough numbers or format is incorrect!" << endl;
            inputFile.close();
            return;
        }
    }
    inputFile.close();

    string outputFilename;
    cout << "Enter output filename: ";
    cin >> outputFilename;

    ofstream outputFile(outputFilename);
    if (!outputFile.is_open()) {
        cout << "Error: Cannot create output file!" << endl;
        return;
    }

    outputFile << fixed << setprecision(6);
    for (int i = 0; i < n; ++i) {
        double result = pow(x[i], m[i]);
        outputFile << result << endl;
    }
    outputFile.close();

    cout << "Results written to " << outputFilename << endl;
}

void task5() {
    cout << "\nTask 5: Reverse square roots" << endl;

    string filename;
    cout << "Enter input filename: ";
    cin >> filename;

    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Error: Cannot open file " << filename << endl;
        return;
    }

    vector<unsigned long long> numbers;
    unsigned long long num;

    while (inputFile >> num) {
        numbers.push_back(num);
    }
    inputFile.close();

    if (numbers.empty()) {
        cout << "Error: No numbers found in file!" << endl;
        return;
    }

    cout << "Results:" << endl;
    cout << fixed << setprecision(3);

    for (auto it = numbers.rbegin(); it != numbers.rend(); ++it) {
        double squareRoot = sqrt(*it);
        cout << squareRoot << endl;
    }
}

int main() {
    int choice;

    do {
        displayMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            task1();
            break;
        case 2:
            task2();
            break;
        case 3:
            task3();
            break;
        case 4:
            task4();
            break;
        case 5:
            task5();
            break;
        case 0:
            cout << "Bye!" << endl;
            break;
        default:
            cout << "Invalid choice, try again." << endl;
            break;
        }

        if (choice != 0) {
            cout << "\nPress Enter to continue...";
            cin.get();
        }

    } while (choice != 0);

    return 0;
}