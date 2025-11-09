#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <limits>

using namespace std;

// task 1
double calculateExpression(const string& expression) {
    double result = 0.0;
    char currentOp = '+';
    string currentNum = "";

    for (size_t i = 0; i < expression.length(); i++) {
        char c = expression[i];

        if (isdigit(c) || c == '.' || (c == '-' && currentNum.empty())) {
            currentNum += c;
        }
        else if (c == '+' || c == '-') {
            if (!currentNum.empty()) {
                double num = stod(currentNum);
                if (currentOp == '+') result += num;
                else if (currentOp == '-') result -= num;
                currentNum = "";
            }
            currentOp = c;
            currentNum += c;
        }
    }

    if (!currentNum.empty()) {
        double num = stod(currentNum);
        if (currentOp == '+') result += num;
        else if (currentOp == '-') result -= num;
    }

    return result;
}

void task1() {
    cout << "\n~~~ TASK 1: Algebraic Expression Calculator." << endl;

    string filename;
    cout << "Enter input filename: ";
    cin >> filename;

    ifstream file(filename);
    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }

    string expression;
    getline(file, expression);
    file.close();

    size_t equalPos = expression.find('=');
    if (equalPos != string::npos) {
        expression = expression.substr(0, equalPos);
    }

    cout << "Expression: " << expression << endl;

    try {
        double result = calculateExpression(expression);
        cout << "Result: " << result << endl;

        ofstream outFile("task1_result.txt");
        outFile << expression << " = " << result;
        outFile.close();
        cout << "Result saved to task1_result.txt" << endl;
    }
    catch (const exception& e) {
        cout << "Error calculating expression: " << e.what() << endl;
    }
}

// task 2
string capitalizeAfterArticles(const string& text) {
    vector<string> articles = { "die", "der", "das" };
    string result = text;
    size_t pos = 0;

    for (const auto& article : articles) {
        pos = 0;
        string searchStr = article + " ";
        while ((pos = result.find(searchStr, pos)) != string::npos) {
            size_t wordStart = pos + searchStr.length();
            if (wordStart < result.length() && isalpha(result[wordStart])) {
                result[wordStart] = toupper(result[wordStart]);
            }
            pos += searchStr.length();
        }
    }

    return result;
}

void task2() {
    cout << "\n~~~ TASK 2: Capitalize After German Articles." << endl;

    string filename;
    cout << "Enter input filename: ";
    cin >> filename;

    ifstream file(filename);
    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }

    string line, text;
    while (getline(file, line)) {
        text += line + "\n";
    }
    file.close();

    cout << "Original text:" << endl;
    cout << text << endl;

    string result = capitalizeAfterArticles(text);

    cout << "Modified text:" << endl;
    cout << result << endl;

    ofstream outFile("task2_result.txt");
    outFile << result;
    outFile.close();
    cout << "Result saved to task2_result.txt" << endl;
}

// task 3
string reverseWord(const string& word) {
    string reversed = word;

    string punctuation = "";
    while (!reversed.empty() && ispunct(reversed.back())) {
        punctuation = reversed.back() + punctuation;
        reversed.pop_back();
    }

    reverse(reversed.begin(), reversed.end());
    return reversed + punctuation;
}

string decryptText(const string& text) {
    string result;
    string currentWord;

    for (char c : text) {
        if (isalnum(c)) {
            currentWord += c;
        }
        else {
            if (!currentWord.empty()) {
                result += reverseWord(currentWord);
                currentWord.clear();
            }
            result += c;
        }
    }

    if (!currentWord.empty()) {
        result += reverseWord(currentWord);
    }

    return result;
}

void task3() {
    cout << "\n~~~ TASK 3: Decrypt Reversed Words." << endl;

    string inputFilename, outputFilename;
    cout << "Enter input filename: ";
    cin >> inputFilename;
    cout << "Enter output filename: ";
    cin >> outputFilename;

    ifstream inputFile(inputFilename);
    if (!inputFile) {
        cout << "Error opening input file!" << endl;
        return;
    }

    string line, encryptedText;
    while (getline(inputFile, line)) {
        encryptedText += line + "\n";
    }
    inputFile.close();

    cout << "Encrypted text:" << endl;
    cout << encryptedText << endl;

    string decryptedText = decryptText(encryptedText);

    cout << "Decrypted text:" << endl;
    cout << decryptedText << endl;

    ofstream outputFile(outputFilename);
    outputFile << decryptedText;
    outputFile.close();

    cout << "Decrypted text saved to " << outputFilename << endl;
}

// task 4
bool checkTDTags(const string& text) {
    int openCount = 0;
    int closeCount = 0;
    size_t pos = 0;

    while (pos < text.length()) {
        size_t openPos = text.find("<td", pos);
        if (openPos != string::npos) {
            size_t tagEnd = text.find('>', openPos);
            if (tagEnd != string::npos) {
                string tagContent = text.substr(openPos, tagEnd - openPos + 1);
                if (tagContent == "<td>" || tagContent.find("<td ") == 0) {
                    openCount++;
                    pos = tagEnd + 1;
                    continue;
                }
            }
        }

        size_t closePos = text.find("</td>", pos);
        if (closePos != string::npos) {
            closeCount++;
            pos = closePos + 5;
            continue;
        }

        break;
    }

    return openCount == closeCount;
}

void task4() {
    cout << "\n~~~ TASK 4: Check TD Tags Balance." << endl;

    string filename;
    cout << "Enter input filename: ";
    cin >> filename;

    ifstream file(filename);
    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }

    string line, htmlText;
    while (getline(file, line)) {
        htmlText += line + "\n";
    }
    file.close();

    cout << "Checking HTML text..." << endl;
    cout << htmlText << endl;

    bool isValid = checkTDTags(htmlText);

    if (isValid) {
        cout << "SUCCESS: All <td> tags are properly balanced!" << endl;
    }
    else {
        cout << "ERROR: Mismatched <td> tags detected!" << endl;
    }

    ofstream outFile("task4_result.txt");
    outFile << "TD Tags Check Result: " << (isValid ? "VALID" : "INVALID") << endl;
    outFile << "Text analyzed:" << endl;
    outFile << htmlText << endl;
    outFile.close();
}

// task 5
struct Student {
    string surname;
    int course;
    string group;
    vector<int> grades;
    double average;
};

void createStudentFile(const string& filename, int N) {
    ofstream file(filename);

    vector<string> surnames = { "Smith", "Johnson", "Williams", "Brown", "Jones",
                              "Miller", "Davis", "Garcia", "Rodriguez", "Wilson" };
    vector<string> groups = { "A1", "B2", "C3", "D4", "E5" };

    srand(time(0));

    for (int i = 0; i < N; i++) {
        string surname = surnames[rand() % surnames.size()];
        int course = 1 + rand() % 4;
        string group = groups[rand() % groups.size()];
        int gradeCount = 3 + rand() % 4;

        file << surname << " " << course << " " << group;

        for (int j = 0; j < gradeCount; j++) {
            int grade = 2 + rand() % 4;
            file << "," << grade;
        }
        file << endl;
    }

    file.close();
    cout << "Created file with " << N << " students: " << filename << endl;
}

Student findWorstStudent(const string& filename) {
    ifstream file(filename);
    if (!file) {
        throw runtime_error("Cannot open file: " + filename);
    }

    vector<Student> students;
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        Student student;

        ss >> student.surname >> student.course >> student.group;

        string gradesStr;
        getline(ss, gradesStr);

        stringstream gradeStream(gradesStr);
        string grade;
        int sum = 0;
        int count = 0;

        while (getline(gradeStream, grade, ',')) {
            if (!grade.empty()) {
                int g = stoi(grade);
                student.grades.push_back(g);
                sum += g;
                count++;
            }
        }

        if (count > 0) {
            student.average = static_cast<double>(sum) / count;
        }
        else {
            student.average = 0.0;
        }

        students.push_back(student);
    }
    file.close();

    if (students.empty()) {
        throw runtime_error("No students found in file");
    }

    Student worst = students[0];
    for (const auto& student : students) {
        if (student.average < worst.average) {
            worst = student;
        }
    }

    return worst;
}

void task5() {
    cout << "\n~~~ TASK 5: Find Student with Worst Average ===" << endl;

    string filename;
    int N;

    cout << "Enter filename for student data: ";
    cin >> filename;
    cout << "Enter number of students to generate: ";
    cin >> N;

    try {
        createStudentFile(filename, N);

        Student worst = findWorstStudent(filename);

        cout << "\nStudent with worst average grade:" << endl;
        cout << "Surname: " << worst.surname << endl;
        cout << "Course: " << worst.course << endl;
        cout << "Group: " << worst.group << endl;
        cout << "Grades: ";
        for (int grade : worst.grades) {
            cout << grade << " ";
        }
        cout << endl;
        cout << fixed << setprecision(2);
        cout << "Average: " << worst.average << endl;

        ofstream resultFile("task5_result.txt");
        resultFile << "Student with worst average grade:" << endl;
        resultFile << "Surname: " << worst.surname << endl;
        resultFile << "Course: " << worst.course << endl;
        resultFile << "Group: " << worst.group << endl;
        resultFile << "Grades: ";
        for (int grade : worst.grades) {
            resultFile << grade << " ";
        }
        resultFile << endl;
        resultFile << fixed << setprecision(2);
        resultFile << "Average: " << worst.average << endl;
        resultFile.close();

        cout << "Result saved to task5_result.txt" << endl;

    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}

// main menu
void displayMenu() {
    cout << "~~~ MAIN MENU ~~~" << endl;
    cout << "1. Algebraic Expression Calculator" << endl;
    cout << "2. Capitalize After German Articles" << endl;
    cout << "3. Decrypt Reversed Words" << endl;
    cout << "4. Check TD Tags Balance" << endl;
    cout << "5. Find Student with Worst Average" << endl;
    cout << "0. Exit" << endl;
    cout << "~~~" << endl;
    cout << "Enter your choice (0-5): ";
}

int main() {
    int choice;

    do {
        displayMenu();
        cin >> choice;

        try {
            switch (choice) {
            case 1: task1(); break;
            case 2: task2(); break;
            case 3: task3(); break;
            case 4: task4(); break;
            case 5: task5(); break;
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