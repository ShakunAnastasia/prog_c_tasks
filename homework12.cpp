#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <tuple>

using namespace std;

const double M_PI = 3.14159265358979323846;

void displayMenu() {
    cout << "~~~TASK SELECTION~~~" << endl;
    cout << "6. Logarithm Calculation" << endl;
    cout << "7. Arcsine from File" << endl;
    cout << "8. Exponential to File" << endl;
    cout << "9. Replace with Squares" << endl;
    cout << "10. Clean CSV File" << endl;
    cout << "11. Absolute Values" << endl;
    cout << "12. Harmonic Mean" << endl;
    cout << "13. Power with Precision" << endl;
    cout << "14. Dynamic Root Table" << endl;
    cout << "15. Geometric Mean" << endl;
    cout << "16. Square Roots to File" << endl;
    cout << "17. Geometric Figures" << endl;
    cout << "18. Sort Segments by Length" << endl;
    cout << "19. Longest 3D Segment" << endl;
    cout << "20. Max Lever Force Points" << endl;
    cout << "21. Oldest and Newest Dates" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter your choice (6-21): ";
}

void task6() {
    cout << "\n~Task 6: Logarithm Calculation " << endl;

    string input;
    cout << "Enter real numbers separated by commas: ";
    cin.ignore();
    getline(cin, input);

    vector<double> numbers;
    stringstream ss(input);
    string token;

    while (getline(ss, token, ',')) {
        token.erase(0, token.find_first_not_of(" \t"));
        token.erase(token.find_last_not_of(" \t") + 1);

        if (!token.empty()) {
            try {
                numbers.push_back(stod(token));
            }
            catch (...) {
                cout << "Warning: Skipping invalid number '" << token << "'" << endl;
            }
        }
    }

    cout << "Results:" << endl;
    for (double num : numbers) {
        if (num <= 0) {
            cout << setw(5) << "None" << endl;
        }
        else {
            double logResult = log(num);

            stringstream decimalStream, scientificStream;

            decimalStream << fixed << setprecision(3) << logResult;
            string decimalStr = decimalStream.str();

            if (decimalStr.length() > 5) {
                decimalStr = decimalStr.substr(0, 5);
            }
            else {
                decimalStr = string(5 - decimalStr.length(), ' ') + decimalStr;
            }

            scientificStream << scientific << setprecision(0) << logResult;
            string scientificStr = scientificStream.str();

            size_t ePos = scientificStr.find('e');
            if (ePos != string::npos) {
                string mantissa = scientificStr.substr(0, ePos);
                if (mantissa.length() > 3) mantissa = mantissa.substr(0, 3);
                string exponent = scientificStr.substr(ePos, 2);
                scientificStr = mantissa + exponent;
            }

            if (scientificStr.length() > 5) {
                scientificStr = scientificStr.substr(0, 5);
            }
            else {
                scientificStr = string(5 - scientificStr.length(), ' ') + scientificStr;
            }

            cout << "Decimal: " << decimalStr << " | Scientific: " << scientificStr << endl;
        }
    }
}

void task7() {
    cout << "\n~Task 7: Arcsine Calculation from File" << endl;

    string inputFilename, outputFilename;
    cout << "Enter input filename: ";
    cin >> inputFilename;
    cout << "Enter output filename: ";
    cin >> outputFilename;

    ifstream inputFile(inputFilename);
    if (!inputFile.is_open()) {
        cout << "Error: Cannot open input file!" << endl;
        return;
    }

    string line;
    getline(inputFile, line);
    inputFile.close();

    vector<double> numbers;
    stringstream ss(line);
    string token;

    while (getline(ss, token, ';')) {
        token.erase(0, token.find_first_not_of(" \t"));
        token.erase(token.find_last_not_of(" \t") + 1);

        if (!token.empty()) {
            try {
                numbers.push_back(stod(token));
            }
            catch (...) {
                cout << "Warning: Skipping invalid number '" << token << "'" << endl;
            }
        }
    }

    ofstream outputFile(outputFilename);
    if (!outputFile.is_open()) {
        cout << "Error: Cannot create output file!" << endl;
        return;
    }

    outputFile << scientific << setprecision(6);
    for (double num : numbers) {
        if (num >= -1.0 && num <= 1.0) {
            double arcsinResult = asin(num);
            outputFile << arcsinResult << endl;
        }
    }
    outputFile.close();

    cout << "Results written to " << outputFilename << endl;
}

void task8() {
    cout << "\n~Task 8: Exponential Values to File" << endl;

    string filename;
    cout << "Enter filename: ";
    cin >> filename;

    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Error: Cannot open file!" << endl;
        return;
    }

    vector<int> numbers;
    int num;
    while (inputFile >> num) {
        numbers.push_back(num);
    }
    inputFile.close();

    ofstream outputFile(filename, ios::app);
    if (!outputFile.is_open()) {
        cout << "Error: Cannot open file for writing!" << endl;
        return;
    }

    outputFile << "\nExponential values:\n";
    for (int n : numbers) {
        double expValue = exp(n);
        outputFile << setw(6) << fixed << setprecision(2) << expValue << endl;
    }
    outputFile.close();

    cout << "Exponential values appended to " << filename << endl;
}

void task9() {
    cout << "\n~Task 9: Replace with Squares" << endl;

    string filename;
    cout << "Enter filename: ";
    cin >> filename;

    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Error: Cannot open file!" << endl;
        return;
    }

    vector<int> numbers;
    int num;
    while (inputFile >> num) {
        numbers.push_back(num);
    }
    inputFile.close();

    for (size_t i = 0; i < numbers.size() - 1; ++i) {
        if (numbers[i] > numbers[i + 1]) {
            numbers[i] = numbers[i] * numbers[i];
        }
    }

    ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        cout << "Error: Cannot create output file!" << endl;
        return;
    }

    for (size_t i = 0; i < numbers.size(); ++i) {
        outputFile << numbers[i];
        if (i < numbers.size() - 1) outputFile << " ";
    }
    outputFile.close();

    cout << "File updated successfully!" << endl;
}

void task10() {
    cout << "\n~Task 10: Clean CSV File" << endl;

    string inputFilename, outputFilename;
    cout << "Enter input filename: ";
    cin >> inputFilename;
    cout << "Enter output filename: ";
    cin >> outputFilename;

    ifstream inputFile(inputFilename);
    if (!inputFile.is_open()) {
        cout << "Error: Cannot open input file!" << endl;
        return;
    }

    string line;
    vector<int> numbers;

    while (getline(inputFile, line)) {
        stringstream ss(line);
        string token;
        while (getline(ss, token, ',')) {
            token.erase(0, token.find_first_not_of(" \t"));
            token.erase(token.find_last_not_of(" \t") + 1);

            if (!token.empty()) {
                try {
                    numbers.push_back(stoi(token));
                }
                catch (...) {
                }
            }
        }
    }
    inputFile.close();

    ofstream outputFile(outputFilename);
    if (!outputFile.is_open()) {
        cout << "Error: Cannot create output file!" << endl;
        return;
    }

    for (size_t i = 0; i < numbers.size(); ++i) {
        outputFile << numbers[i];
        if (i < numbers.size() - 1) outputFile << " ";
    }
    outputFile.close();

    cout << "File cleaned and saved as " << outputFilename << endl;
}

void task11() {
    cout << "\n~Task 11: Absolute Values" << endl;

    string inputFilename, outputFilename;
    cout << "Enter input filename: ";
    cin >> inputFilename;
    cout << "Enter output filename: ";
    cin >> outputFilename;

    ifstream inputFile(inputFilename);
    if (!inputFile.is_open()) {
        cout << "Error: Cannot open input file!" << endl;
        return;
    }

    string line;
    vector<double> numbers;

    getline(inputFile, line);
    inputFile.close();

    stringstream ss(line);
    string token;
    int maxPrecision = 0;

    while (getline(ss, token, ';')) {
        token.erase(0, token.find_first_not_of(" \t"));
        token.erase(token.find_last_not_of(" \t") + 1);

        if (!token.empty()) {
            try {
                double num = stod(token);
                numbers.push_back(abs(num));

                size_t dotPos = token.find('.');
                if (dotPos != string::npos) {
                    int precision = token.length() - dotPos - 1;
                    if (precision > maxPrecision) {
                        maxPrecision = precision;
                    }
                }
            }
            catch (...) {
                cout << "Warning: Skipping invalid number" << endl;
            }
        }
    }

    ofstream outputFile(outputFilename);
    if (!outputFile.is_open()) {
        cout << "Error: Cannot create output file!" << endl;
        return;
    }

    for (double num : numbers) {
        outputFile << fixed << setprecision(maxPrecision) << num << endl;
    }
    outputFile.close();

    cout << "Absolute values written to " << outputFilename << " with precision " << maxPrecision << endl;
}

void task12() {
    cout << "\n~Task 12: Harmonic Mean" << endl;

    string input;
    cout << "Enter three numbers in format A=xxx.xxx, B=xxExxx C=xxx.xxxx: ";
    cin.ignore();
    getline(cin, input);

    vector<double> numbers;
    stringstream ss(input);
    string token;

    while (getline(ss, token, ' ')) {
        if (token.empty()) continue;

        size_t eqPos = token.find('=');
        if (eqPos != string::npos) {
            string numStr = token.substr(eqPos + 1);
            try {
                numbers.push_back(stod(numStr));
            }
            catch (...) {
                cout << "Error parsing number: " << numStr << endl;
                return;
            }
        }
    }

    if (numbers.size() != 3) {
        cout << "Error: Exactly three numbers required!" << endl;
        return;
    }

    bool hasZero = false;
    for (double num : numbers) {
        if (num == 0) {
            hasZero = true;
            break;
        }
    }

    if (hasZero) {
        cout << "Error: Cannot calculate harmonic mean - one of the numbers is zero!" << endl;
        return;
    }

    double harmonicMean = 3.0 / (1.0 / numbers[0] + 1.0 / numbers[1] + 1.0 / numbers[2]);

    cout << "Harmonic mean:" << endl;
    cout << "Decimal: " << fixed << harmonicMean << endl;
    cout << "Scientific: " << scientific << harmonicMean << endl;
}

void task13() {
    cout << "\n~Task 13: Power with Precision" << endl;

    double x;
    int k;
    cout << "Enter number (-10000 to 10000): ";
    cin >> x;
    cout << "Enter power (|k| < 10): ";
    cin >> k;

    if (x < -10000 || x > 10000 || k <= -10 || k >= 10) {
        cout << "Error: Invalid input range!" << endl;
        return;
    }

    double result = pow(x, k);

    cout << "Result with high precision:" << endl;
    cout << fixed << setprecision(20) << result << endl;
    cout << "With 4 decimal places: " << fixed << setprecision(4) << result << endl;
}

void task14() {
    cout << "\n~Task 14: Dynamic Root Table" << endl;

    int n;
    cout << "Enter n: ";
    cin >> n;

    const int COLUMNS_PER_ROW = 8;
    int totalRows = (n + COLUMNS_PER_ROW - 1) / COLUMNS_PER_ROW;

    for (int row = 0; row < totalRows; ++row) {
        for (int col = 0; col < COLUMNS_PER_ROW; ++col) {
            int num = row * COLUMNS_PER_ROW + col + 1;
            if (num > n) break;
            cout << left << setw(8) << num;
        }
        cout << endl;

        for (int col = 0; col < COLUMNS_PER_ROW; ++col) {
            int num = row * COLUMNS_PER_ROW + col + 1;
            if (num > n) break;

            double root = sqrt(num);
            if (root == floor(root)) {
                cout << left << setw(8) << fixed << setprecision(0) << root;
            }
            else {
                cout << left << setw(8) << fixed << setprecision(2) << root;
            }
        }
        cout << endl << endl;
    }
}

void task15() {
    cout << "\n~Task 15: Geometric Mean" << endl;

    string filename;
    cout << "Enter filename: ";
    cin >> filename;

    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Error: Cannot open file!" << endl;
        return;
    }

    vector<double> numbers;
    double num;
    while (inputFile >> num) {
        numbers.push_back(num);
    }
    inputFile.close();

    if (numbers.empty()) {
        cout << "Error: No numbers found in file!" << endl;
        return;
    }

    double product = 1.0;
    for (double n : numbers) {
        product *= n;
    }

    double geometricMean = pow(product, 1.0 / numbers.size());

    cout << "Geometric mean: " << geometricMean << endl;
}

void task16() {
    cout << "\n~Task 16: Square Roots to File" << endl;

    string inputFilename, outputFilename;
    cout << "Enter input filename (F): ";
    cin >> inputFilename;
    cout << "Enter output filename: ";
    cin >> outputFilename;

    ifstream inputFile(inputFilename);
    if (!inputFile.is_open()) {
        cout << "Error: Cannot open input file!" << endl;
        return;
    }

    vector<double> numbers;
    string line;

    while (getline(inputFile, line)) {
        stringstream ss(line);
        string token;
        while (getline(ss, token, '\t')) {
            if (!token.empty()) {
                try {
                    double num = stod(token);
                    if (num > 0) {
                        numbers.push_back(num);
                    }
                }
                catch (...) {
                }
            }
        }
    }
    inputFile.close();

    ofstream outputFile(outputFilename);
    if (!outputFile.is_open()) {
        cout << "Error: Cannot create output file!" << endl;
        return;
    }

    for (double num : numbers) {
        double root = sqrt(num);
        outputFile << fixed << setprecision(5) << num << "," << root << endl;
    }
    outputFile.close();

    cout << "Positive numbers with square roots written to " << outputFilename << endl;
}

void task17() {
    cout << "\n~Task 17: Geometric Figures" << endl;

    string filename;
    cout << "Enter filename: ";
    cin >> filename;

    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Error: Cannot open file!" << endl;
        return;
    }

    double maxSegmentLength = 0;
    double maxRectanglePerimeter = 0;
    double minCircleArea = numeric_limits<double>::max();

    string line;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        int figureType;
        ss >> figureType;

        if (figureType == 1) { // Segment
            double x1, y1, x2, y2;
            if (ss >> x1 >> y1 >> x2 >> y2) {
                double length = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
                if (length > maxSegmentLength) {
                    maxSegmentLength = length;
                }
            }
        }
        else if (figureType == 2) { // Rectangle
            double x1, y1, x2, y2;
            if (ss >> x1 >> y1 >> x2 >> y2) {
                double width = abs(x2 - x1);
                double height = abs(y2 - y1);
                double perimeter = 2 * (width + height);
                if (perimeter > maxRectanglePerimeter) {
                    maxRectanglePerimeter = perimeter;
                }
            }
        }
        else if (figureType == 3) { // Circle
            double x, y, radius;
            if (ss >> x >> y >> radius) {
                double area = M_PI * radius * radius;
                if (area < minCircleArea) {
                    minCircleArea = area;
                }
            }
        }
    }
    inputFile.close();

    cout << "Results:" << endl;
    cout << "Longest segment: " << maxSegmentLength << endl;
    cout << "Largest rectangle perimeter: " << maxRectanglePerimeter << endl;
    cout << "Smallest circle area: " << minCircleArea << endl;
}

void task18() {
    cout << "\n~Task 18: Sort Segments by Length" << endl;

    string inputFilename, outputFilename;
    cout << "Enter input filename: ";
    cin >> inputFilename;
    cout << "Enter output filename: ";
    cin >> outputFilename;

    ifstream inputFile(inputFilename);
    if (!inputFile.is_open()) {
        cout << "Error: Cannot open input file!" << endl;
        return;
    }

    string line;
    getline(inputFile, line);
    inputFile.close();

    vector<pair<int, int>> points;
    stringstream ss(line);
    string token;

    while (getline(ss, token, ')')) {
        if (token.empty()) continue;

        size_t start = token.find('(');
        if (start != string::npos) {
            string coords = token.substr(start + 1);
            stringstream coordSS(coords);
            int x, y;
            char comma;
            if (coordSS >> x >> comma >> y) {
                points.emplace_back(x, y);
            }
        }
    }

    vector<tuple<double, int, int, int, int>> segments;

    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = i + 1; j < points.size(); ++j) {
            double length = sqrt(pow(points[j].first - points[i].first, 2) +
                pow(points[j].second - points[i].second, 2));
            segments.emplace_back(length, points[i].first, points[i].second,
                points[j].first, points[j].second);
        }
    }

    sort(segments.begin(), segments.end());

    ofstream outputFile(outputFilename);
    if (!outputFile.is_open()) {
        cout << "Error: Cannot create output file!" << endl;
        return;
    }

    for (const auto& seg : segments) {
        outputFile << "(" << get<1>(seg) << ", " << get<2>(seg) << "), ("
            << get<3>(seg) << ", " << get<4>(seg) << ")" << endl;
    }
    outputFile.close();

    cout << "Sorted segments written to " << outputFilename << endl;
}

void task19() {
    cout << "\n~Task 19: Longest 3D Segment" << endl;

    string filename;
    cout << "Enter filename: ";
    cin >> filename;

    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Error: Cannot open file!" << endl;
        return;
    }

    string line;
    getline(inputFile, line);
    inputFile.close();

    vector<tuple<int, int, int>> points;
    stringstream ss(line);
    string token;

    while (getline(ss, token, ';')) {
        if (token.empty()) continue;

        stringstream pointSS(token);
        int x, y, z;
        char comma;
        if (pointSS >> x >> comma >> y >> comma >> z) {
            points.emplace_back(x, y, z);
        }
    }

    double maxLength = 0;
    tuple<int, int, int> p1, p2;

    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = i + 1; j < points.size(); ++j) {
            double length = sqrt(pow(get<0>(points[j]) - get<0>(points[i]), 2) +
                pow(get<1>(points[j]) - get<1>(points[i]), 2) +
                pow(get<2>(points[j]) - get<2>(points[i]), 2));
            if (length > maxLength) {
                maxLength = length;
                p1 = points[i];
                p2 = points[j];
            }
        }
    }

    cout << "Longest segment: " << maxLength << endl;
    cout << "Between points: (" << get<0>(p1) << ", " << get<1>(p1) << ", " << get<2>(p1) << ") and ("
        << get<0>(p2) << ", " << get<1>(p2) << ", " << get<2>(p2) << ")" << endl;
}

void task20() {
    cout << "\n~Task 20: Max Lever Force Points" << endl;

    string filename;
    cout << "Enter filename: ";
    cin >> filename;

    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Error: Cannot open file!" << endl;
        return;
    }

    string line;
    getline(inputFile, line);
    inputFile.close();

    vector<tuple<int, int, double>> points;
    stringstream ss(line);
    string token;

    while (getline(ss, token, ']')) {
        if (token.empty()) continue;

        size_t start = token.find('[');
        if (start != string::npos) {
            string data = token.substr(start + 1);
            stringstream dataSS(data);
            int x, y;
            double mass;
            char comma;
            if (dataSS >> x >> comma >> y >> comma >> mass) {
                points.emplace_back(x, y, mass);
            }
        }
    }

    double maxForce1 = -1, maxForce2 = -1;
    tuple<int, int, double> point1, point2;

    for (size_t i = 0; i < points.size(); ++i) {
        double force = get<2>(points[i]) * (get<0>(points[i]) + get<1>(points[i]));

        if (force > maxForce1) {
            maxForce2 = maxForce1;
            point2 = point1;
            maxForce1 = force;
            point1 = points[i];
        }
        else if (force > maxForce2) {
            maxForce2 = force;
            point2 = points[i];
        }
    }

    cout << "Two points with maximum lever force:" << endl;
    cout << "Point 1: (" << get<0>(point1) << ", " << get<1>(point1) << ", mass="
        << get<2>(point1) << "), force=" << maxForce1 << endl;
    cout << "Point 2: (" << get<0>(point2) << ", " << get<1>(point2) << ", mass="
        << get<2>(point2) << "), force=" << maxForce2 << endl;
}

void task21() {
    cout << "\n~Task 21: Oldest and Newest Dates" << endl;

    string inputFilename, outputFilename;
    cout << "Enter input filename: ";
    cin >> inputFilename;
    cout << "Enter output filename: ";
    cin >> outputFilename;

    ifstream inputFile(inputFilename);
    if (!inputFile.is_open()) {
        cout << "Error: Cannot open input file!" << endl;
        return;
    }

    string line;
    getline(inputFile, line);
    inputFile.close();

    vector<tuple<int, int, int>> dates;
    stringstream ss(line);
    string token;

    while (getline(ss, token, ')')) {
        if (token.empty()) continue;

        size_t start = token.find('(');
        if (start != string::npos) {
            string dateStr = token.substr(start + 1);
            for (char& c : dateStr) {
                if (c == '.' || c == '/') c = ' ';
            }

            stringstream dateSS(dateStr);
            int day, month, year;
            if (dateSS >> day >> month >> year) {
                if (year >= 0 && year <= 49) year += 2000;
                else if (year >= 50 && year <= 99) year += 1900;

                if (year >= 1951 && year <= 2049) {
                    dates.emplace_back(year, month, day);
                }
            }
        }
    }

    if (dates.empty()) {
        cout << "No valid dates found!" << endl;
        return;
    }

    auto oldest = dates[0], newest = dates[0];

    for (const auto& date : dates) {
        if (get<0>(date) < get<0>(oldest) ||
            (get<0>(date) == get<0>(oldest) && get<1>(date) < get<1>(oldest)) ||
            (get<0>(date) == get<0>(oldest) && get<1>(date) == get<1>(oldest) && get<2>(date) < get<2>(oldest))) {
            oldest = date;
        }

        if (get<0>(date) > get<0>(newest) ||
            (get<0>(date) == get<0>(newest) && get<1>(date) > get<1>(newest)) ||
            (get<0>(date) == get<0>(newest) && get<1>(date) == get<1>(newest) && get<2>(date) > get<2>(newest))) {
            newest = date;
        }
    }

    ofstream outputFile(outputFilename);
    if (!outputFile.is_open()) {
        cout << "Error: Cannot create output file!" << endl;
        return;
    }

    outputFile << "Oldest date: " << get<2>(oldest) << "." << get<1>(oldest) << "." << get<0>(oldest) << endl;
    outputFile << "Newest date: " << get<2>(newest) << "." << get<1>(newest) << "." << get<0>(newest) << endl;
    outputFile.close();

    cout << "Dates written to " << outputFilename << endl;
}

int main() {
    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
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
        case 19: task19(); break;
        case 20: task20(); break;
        case 21: task21(); break;
        case 0: cout << "Bye!" << endl; break;
        default: cout << "Invalid choice!" << endl; break;
        }

        if (choice != 0) {
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }

    } while (choice != 0);

    return 0;
}