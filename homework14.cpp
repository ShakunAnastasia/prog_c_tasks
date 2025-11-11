#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <cmath>
#include <random>
#include <map>

using namespace std;

void task5() {
    cout << "\n~~~ TASK 5: Count lines with specific patterns." << endl;

    string filename;
    cout << "Enter filename: ";
    cin >> filename;

    ifstream file(filename);
    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }

    char startChar, endChar;
    cout << "Enter start character: ";
    cin >> startChar;
    cout << "Enter end character: ";
    cin >> endChar;

    int countStart = 0, countEnd = 0, countSame = 0, countSameChars = 0;
    string line;

    while (getline(file, line)) {
        if (line.empty()) continue;

        if (line[0] == startChar) countStart++;
        if (!line.empty() && line.back() == endChar) countEnd++;
        if (!line.empty() && line[0] == line.back()) countSame++;

        bool allSame = true;
        for (size_t i = 1; i < line.length(); i++) {
            if (line[i] != line[0]) {
                allSame = false;
                break;
            }
        }
        if (allSame && !line.empty()) countSameChars++;
    }
    file.close();

    cout << "Lines starting with '" << startChar << "': " << countStart << endl;
    cout << "Lines ending with '" << endChar << "': " << countEnd << endl;
    cout << "Lines starting and ending with same character: " << countSame << endl;
    cout << "Lines with all same characters: " << countSameChars << endl;
}

struct Student6 {
    string surname;
    string name;
    string group;
    vector<double> grades;
};

void task6() {
    cout << "\n~~~ TASK 6: Student average by group." << endl;

    string filename;
    int N;
    cout << "Enter filename: ";
    cin >> filename;
    cout << "Enter number of students: ";
    cin >> N;

    ofstream file(filename);
    if (!file) {
        cout << "Error creating file!" << endl;
        return;
    }

    vector<string> surnames = { "Smith", "Johnson", "Brown", "Wilson", "Davis" };
    vector<string> names = { "John", "Alice", "Bob", "Emma", "Mike" };
    vector<string> groups = { "A1", "B2", "C3" };

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> gradeDist(2.0, 5.0);

    for (int i = 0; i < N; i++) {
        file << surnames[i % surnames.size()] << " "
            << names[i % names.size()] << " "
            << groups[i % groups.size()] << " ";

        int gradeCount = 3 + rand() % 3;
        for (int j = 0; j < gradeCount; j++) {
            file << fixed << setprecision(1) << gradeDist(gen);
            if (j < gradeCount - 1) file << " ";
        }
        file << endl;
    }
    file.close();

    string targetGroup;
    cout << "Enter group to analyze: ";
    cin >> targetGroup;

    ifstream inFile(filename);
    vector<Student6> students;
    string line;

    while (getline(inFile, line)) {
        stringstream ss(line);
        Student6 student;
        ss >> student.surname >> student.name >> student.group;

        if (student.group == targetGroup) {
            double grade;
            while (ss >> grade) {
                student.grades.push_back(grade);
            }
            students.push_back(student);
        }
    }
    inFile.close();

    if (students.empty()) {
        cout << "No students found in group " << targetGroup << endl;
        return;
    }

    double totalSum = 0;
    int totalGrades = 0;

    for (const auto& student : students) {
        double sum = 0;
        for (double grade : student.grades) sum += grade;
        double avg = sum / student.grades.size();
        totalSum += sum;
        totalGrades += student.grades.size();

        cout << student.surname << " " << student.name << ": "
            << fixed << setprecision(2) << avg << endl;
    }

    double overallAvg = totalSum / totalGrades;
    cout << "Overall average for group " << targetGroup << ": "
        << fixed << setprecision(2) << overallAvg << endl;
}

bool isValidTag(const string& tag) {
    return tag.length() >= 3 && tag[0] == '<' && tag.back() == '>';
}

string getTagName(const string& tag) {
    if (tag.length() < 4) return "";
    if (tag[1] == '/') return tag.substr(2, tag.length() - 3);
    return tag.substr(1, tag.length() - 2);
}

void task7() {
    cout << "\n~~~ TASK 7: HTML tag validator." << endl;

    string filename;
    cout << "Enter filename: ";
    cin >> filename;

    ifstream file(filename);
    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }

    string text, line;
    while (getline(file, line)) text += line + "\n";
    file.close();

    vector<string> tags;
    size_t pos = 0;
    while (pos < text.length()) {
        size_t start = text.find('<', pos);
        if (start == string::npos) break;

        size_t end = text.find('>', start);
        if (end == string::npos) break;

        string tag = text.substr(start, end - start + 1);
        if (isValidTag(tag)) {
            tags.push_back(tag);
        }
        pos = end + 1;
    }

    vector<string> stack;
    bool valid = true;

    for (const auto& tag : tags) {
        if (tag[1] != '/') {
            stack.push_back(tag);
        }
        else {
            if (stack.empty()) {
                valid = false;
                break;
            }

            string openTag = stack.back();
            stack.pop_back();

            string openName = getTagName(openTag);
            string closeName = getTagName(tag);

            if (openName != closeName) {
                valid = false;
                break;
            }
        }
    }

    valid = valid && stack.empty();

    cout << "Tags found: " << tags.size() << endl;
    cout << "All tags properly closed: " << (valid ? "YES" : "NO") << endl;

    ofstream result("task7_result.txt");
    result << "Tag validation result: " << (valid ? "VALID" : "INVALID") << endl;
    result.close();
}

void task8() {
    cout << "\n~~~ TASK 8: Multiplication game." << endl;

    string filename = "game_results.txt";
    ofstream file(filename, ios::app);
    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }

    string playerName;
    cout << "Enter your name: ";
    cin >> playerName;

    file << playerName << " ";

    int questionCount;
    cout << "Enter number of questions: ";
    cin >> questionCount;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> numDist(1, 20);

    int correctAnswers = 0;

    for (int i = 0; i < questionCount; i++) {
        int a = numDist(gen);
        int b = numDist(gen);
        int correctAnswer = a * b;
        int userAnswer;

        cout << a << " x " << b << " = ";
        cin >> userAnswer;

        file << a << "x" << b << "=" << userAnswer << " ";

        if (userAnswer == correctAnswer) {
            correctAnswers++;
        }
    }
    file << endl;
    file.close();

    double percentage = (static_cast<double>(correctAnswers) / questionCount) * 100;
    cout << "Your score: " << correctAnswers << "/" << questionCount
        << " (" << fixed << setprecision(1) << percentage << "%)" << endl;
}

void itogi(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }

    map<string, pair<int, int>> playerStats;
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string playerName;
        ss >> playerName;

        int total = 0, correct = 0;
        string question;

        while (ss >> question) {
            size_t eqPos = question.find('=');
            if (eqPos == string::npos) continue;

            size_t xPos = question.find('x');
            if (xPos == string::npos) continue;

            try {
                int a = stoi(question.substr(0, xPos));
                int b = stoi(question.substr(xPos + 1, eqPos - xPos - 1));
                int userAnswer = stoi(question.substr(eqPos + 1));
                int correctAnswer = a * b;

                total++;
                if (userAnswer == correctAnswer) correct++;
            }
            catch (...) {
                continue;
            }
        }

        if (total > 0) {
            playerStats[playerName] = make_pair(correct, total);
        }
    }
    file.close();

    cout << "\n~ GAME RESULTS ~" << endl;
    for (const auto& entry : playerStats) {
        const string& player = entry.first;
        const pair<int, int>& stats = entry.second;
        double percentage = (static_cast<double>(stats.first) / stats.second) * 100;
        cout << player << ": " << stats.first << "/" << stats.second
            << " (" << fixed << setprecision(1) << percentage << "%)" << endl;
    }
}

void task10() {
    cout << "\n~~~ TASK 10: Remove lines multiple of N." << endl;

    string filename;
    int N;
    cout << "Enter filename: ";
    cin >> filename;
    cout << "Enter N: ";
    cin >> N;

    if (N <= 0) {
        cout << "N must be positive!" << endl;
        return;
    }

    ifstream inFile(filename);
    if (!inFile) {
        cout << "Error opening file!" << endl;
        return;
    }

    vector<string> lines;
    string line;
    int lineNum = 0;

    while (getline(inFile, line)) {
        lineNum++;
        if (line.empty()) {
            lines.push_back(line);
            continue;
        }
        if (lineNum % N != 0) {
            lines.push_back(line);
        }
    }
    inFile.close();

    ofstream outFile(filename);
    for (const auto& l : lines) {
        outFile << l << endl;
    }
    outFile.close();

    cout << "File updated successfully!" << endl;
}

void task11() {
    cout << "\n~~~ TASK 11: Center align text." << endl;

    string filename;
    cout << "Enter filename: ";
    cin >> filename;

    ifstream inFile(filename);
    if (!inFile) {
        cout << "Error opening file!" << endl;
        return;
    }

    vector<string> centeredLines;
    string line;
    int maxLength = 0;

    while (getline(inFile, line)) {
        if (line.length() > 50) {
            line = line.substr(0, 50);
        }
        if (line.length() > maxLength) {
            maxLength = line.length();
        }
        centeredLines.push_back(line);
    }
    inFile.close();

    ofstream outFile("centered_" + filename);
    for (auto& l : centeredLines) {
        if (l.empty()) {
            outFile << endl;
            continue;
        }

        int spaces = (maxLength - l.length()) / 2;
        if (l.length() % 2 != maxLength % 2) {
            spaces++;
        }

        outFile << string(spaces, ' ') << l << endl;
    }
    outFile.close();

    cout << "Centered text saved to centered_" << filename << endl;
}

void task12() {
    cout << "\n~~~ TASK 12: Remove extra spaces." << endl;

    string filename;
    int N;
    cout << "Enter filename: ";
    cin >> filename;
    cout << "Enter number of lines: ";
    cin >> N;

    ofstream createFile(filename);
    if (!createFile) {
        cout << "Error creating file!" << endl;
        return;
    }

    cin.ignore();
    for (int i = 0; i < N; i++) {
        string line;
        cout << "Enter line " << i + 1 << ": ";
        getline(cin, line);
        createFile << line << endl;
    }
    createFile.close();

    ifstream inFile(filename);
    vector<string> cleanedLines;
    string line;

    while (getline(inFile, line)) {
        stringstream ss(line);
        string word, cleanedLine;
        bool firstWord = true;

        while (ss >> word) {
            if (!firstWord) cleanedLine += " ";
            cleanedLine += word;
            firstWord = false;
        }
        cleanedLines.push_back(cleanedLine);
    }
    inFile.close();

    ofstream outFile("cleaned_" + filename);
    for (const auto& l : cleanedLines) {
        outFile << l << endl;
    }
    outFile.close();

    cout << "Cleaned file saved to cleaned_" << filename << endl;
}

void task13() {
    cout << "\n~~~ TASK 13: Caesar cipher." << endl;

    string filename;
    int n;
    cout << "Enter filename: ";
    cin >> filename;
    cout << "Enter shift value: ";
    cin >> n;

    ifstream inFile(filename);
    if (!inFile) {
        cout << "Error opening file!" << endl;
        return;
    }

    string text, line;
    while (getline(inFile, line)) text += line + "\n";
    inFile.close();

    string encrypted;
    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            encrypted += static_cast<char>((c - base + n) % 26 + base);
        }
        else {
            encrypted += c;
        }
    }

    ofstream outFile("encrypted_" + filename);
    outFile << encrypted;
    outFile.close();

    cout << "Encrypted text saved to encrypted_" << filename << endl;
}

void task14() {
    cout << "\n~~~ TASK 14: Merge files by lines." << endl;

    string name1, name2;
    cout << "Enter Name1: ";
    cin >> name1;
    cout << "Enter Name2: ";
    cin >> name2;

    ifstream file1(name1), file2(name2);
    if (!file1 || !file2) {
        cout << "Error opening files!" << endl;
        return;
    }

    vector<string> lines1, lines2;
    string line;

    while (getline(file1, line)) lines1.push_back(line);
    while (getline(file2, line)) lines2.push_back(line);

    file1.close();
    file2.close();

    if (lines2.empty()) {
        cout << "Second file is empty!" << endl;
        return;
    }

    ofstream outFile("merged_" + name1);
    for (size_t i = 0; i < lines1.size(); i++) {
        outFile << lines1[i] << lines2[i % lines2.size()] << endl;
    }
    outFile.close();

    cout << "Merged file saved to merged_" << name1 << endl;
}

string toBinary(int num) {
    if (num == 0) return "0";

    string binary;
    unsigned unum;
    if (num < 0) {
        binary = "-";
        unum = -num;
    }
    else {
        unum = num;
    }

    string bits;
    while (unum > 0) {
        bits = (unum % 2 ? '1' : '0') + bits;
        unum /= 2;
    }

    return binary + bits;
}

void task15() {
    cout << "\n~~~ TASK 15: Replace integers with binary." << endl;

    string filename;
    cout << "Enter filename: ";
    cin >> filename;

    ifstream inFile(filename);
    if (!inFile) {
        cout << "Error opening file!" << endl;
        return;
    }

    string text, line;
    while (getline(inFile, line)) text += line + "\n";
    inFile.close();

    string result;
    string currentNum;

    for (size_t i = 0; i < text.length(); i++) {
        char c = text[i];

        if (isdigit(c) || (c == '-' && currentNum.empty()) || (c == '+' && currentNum.empty())) {
            currentNum += c;
        }
        else {
            if (!currentNum.empty()) {
                try {
                    int num = stoi(currentNum);
                    result += toBinary(num);
                }
                catch (...) {
                    result += currentNum;
                }
                currentNum.clear();
            }
            result += c;
        }
    }

    if (!currentNum.empty()) {
        try {
            int num = stoi(currentNum);
            result += toBinary(num);
        }
        catch (...) {
            result += currentNum;
        }
    }

    ofstream outFile("binary_" + filename);
    outFile << result;
    outFile.close();

    cout << "Converted file saved to binary_" << filename << endl;
}

void task16() {
    cout << "\n~~~ TASK 16: Replace numbers with log/exp." << endl;

    string filename;
    cout << "Enter filename: ";
    cin >> filename;

    ifstream inFile(filename);
    if (!inFile) {
        cout << "Error opening file!" << endl;
        return;
    }

    string text, line;
    while (getline(inFile, line)) text += line + "\n";
    inFile.close();

    string result;
    string currentNum;
    bool hasDecimal = false;

    for (size_t i = 0; i < text.length(); i++) {
        char c = text[i];

        if (isdigit(c) || c == '.' || (c == '-' && currentNum.empty()) || (c == '+' && currentNum.empty())) {
            if (c == '.') hasDecimal = true;
            currentNum += c;
        }
        else {
            if (!currentNum.empty()) {
                try {
                    double num = stod(currentNum);
                    if (num > 0) {
                        double logVal = log(num);
                        stringstream ss;
                        ss << fixed << setprecision(6) << logVal;
                        string logStr = ss.str();
                        if (logStr.length() > 10) logStr = logStr.substr(0, 10);
                        result += logStr;
                    }
                    else if (num < 0) {
                        double expVal = exp(num);
                        stringstream ss;
                        ss << fixed << setprecision(4) << expVal;
                        string expStr = ss.str();
                        if (expStr.length() > 7) expStr = expStr.substr(0, 7);
                        result += expStr;
                    }
                    else {
                        result += "0";
                    }
                }
                catch (...) {
                    result += currentNum;
                }
                currentNum.clear();
                hasDecimal = false;
            }
            result += c;
        }
    }

    if (!currentNum.empty()) {
        try {
            double num = stod(currentNum);
            if (num > 0) {
                result += to_string(log(num)).substr(0, 10);
            }
            else if (num < 0) {
                result += to_string(exp(num)).substr(0, 7);
            }
            else {
                result += "0";
            }
        }
        catch (...) {
            result += currentNum;
        }
    }

    ofstream outFile("converted_" + filename);
    outFile << result;
    outFile.close();

    cout << "Converted file saved to converted_" << filename << endl;
}

void task17() {
    cout << "\n~~~ TASK 17: Run-length encoding." << endl;

    string filename;
    cout << "Enter filename: ";
    cin >> filename;

    ifstream inFile(filename);
    if (!inFile) {
        cout << "Error opening file!" << endl;
        return;
    }

    string text, line;
    while (getline(inFile, line)) text += line + "\n";
    inFile.close();

    string encoded;

    for (size_t i = 0; i < text.length();) {
        char current = text[i];
        int count = 1;

        while (i + count < text.length() && text[i + count] == current) {
            count++;
        }

        if (count > 1) {
            encoded += current + to_string(count);
        }
        else {
            encoded += current;
        }

        i += count;
    }

    ofstream outFile("rle_" + filename);
    outFile << encoded;
    outFile.close();

    cout << "Encoded file saved to rle_" << filename << endl;
}

void task18() {
    cout << "\n~~~ TASK 18: Find min/max line lengths." << endl;

    string filename;
    int N;
    cout << "Enter filename: ";
    cin >> filename;
    cout << "Enter number of lines: ";
    cin >> N;

    ofstream createFile(filename);
    if (!createFile) {
        cout << "Error creating file!" << endl;
        return;
    }

    cin.ignore();
    for (int i = 0; i < N; i++) {
        string line;
        cout << "Enter line " << i + 1 << ": ";
        getline(cin, line);
        createFile << line << endl;
    }
    createFile.close();

    ifstream inFile(filename);
    vector<string> lines;
    string line;
    int minLen = INT_MAX, maxLen = 0;

    while (getline(inFile, line)) {
        lines.push_back(line);
        int len = line.length();
        if (len < minLen) minLen = len;
        if (len > maxLen) maxLen = len;
    }
    inFile.close();

    ofstream outFile("extremes_" + filename);
    outFile << "Minimum length: " << minLen << endl;
    outFile << "Maximum length: " << maxLen << endl;
    outFile << "\nLines with minimum length:" << endl;

    for (const auto& l : lines) {
        if (l.length() == minLen) {
            outFile << l << endl;
        }
    }

    outFile << "\nLines with maximum length:" << endl;
    for (const auto& l : lines) {
        if (l.length() == maxLen) {
            outFile << l << endl;
        }
    }
    outFile.close();

    cout << "Extremes saved to extremes_" << filename << endl;
}

void task19() {
    cout << "\n~~~ TASK 19: Words starting with letter." << endl;

    char targetChar;
    string filename;
    cout << "Enter uppercase letter: ";
    cin >> targetChar;
    cout << "Enter filename: ";
    cin >> filename;

    if (!isupper(targetChar)) {
        cout << "Please enter uppercase letter!" << endl;
        return;
    }

    ifstream inFile(filename);
    if (!inFile) {
        cout << "Error opening file!" << endl;
        return;
    }

    string text, line;
    while (getline(inFile, line)) text += line + " ";
    inFile.close();

    vector<string> matchingWords;
    string word;

    for (char c : text) {
        if (isalpha(c)) {
            word += c;
        }
        else {
            if (!word.empty()) {
                char firstChar = word[0];
                if (toupper(firstChar) == targetChar) {
                    matchingWords.push_back(word);
                }
                word.clear();
            }
        }
    }

    ofstream outFile("words_" + string(1, targetChar) + ".txt");
    for (const auto& w : matchingWords) {
        outFile << w << endl;
    }
    outFile.close();

    cout << "Found " << matchingWords.size() << " words starting with '" << targetChar << "'" << endl;
    cout << "Saved to words_" << targetChar << ".txt" << endl;
}

void task20() {
    cout << "\n~~~ TASK 20: Remove lines in range." << endl;

    string filename;
    int N1, N2;
    cout << "Enter filename: ";
    cin >> filename;
    cout << "Enter N1: ";
    cin >> N1;
    cout << "Enter N2: ";
    cin >> N2;

    if (N1 >= N2) {
        cout << "N1 must be less than N2!" << endl;
        return;
    }

    ifstream inFile(filename);
    if (!inFile) {
        cout << "Error opening file!" << endl;
        return;
    }

    vector<string> lines;
    string line;
    int lineNum = 0;

    while (getline(inFile, line)) {
        lineNum++;
        if (lineNum <= N1 || lineNum >= N2) {
            lines.push_back(line);
        }
    }
    inFile.close();

    if (lineNum < N2) {
        cout << "Warning: File has only " << lineNum << " lines" << endl;
    }

    ofstream outFile("removed_" + filename);
    for (const auto& l : lines) {
        outFile << l << endl;
    }
    outFile.close();

    cout << "Modified file saved to removed_" << filename << endl;
}

void task21() {
    cout << "\n~~~ TASK 21: Replace digits with english names." << endl;

    string filename;
    cout << "Enter filename: ";
    cin >> filename;

    ifstream inFile(filename);
    if (!inFile) {
        cout << "Error opening file!" << endl;
        return;
    }

    string text, line;
    while (getline(inFile, line)) text += line + "\n";
    inFile.close();

    map<char, string> digitNames = {
        {'0', "zero"}, {'1', "one"}, {'2', "two"}, {'3', "three"}, {'4', "four"},
        {'5', "five"}, {'6', "six"}, {'7', "seven"}, {'8', "eight"}, {'9', "nine"}
    };

    string result;
    for (char c : text) {
        if (isdigit(c)) {
            result += digitNames[c] + " ";
        }
        else {
            result += c;
        }
    }

    ofstream outFile("digits_" + filename);
    outFile << result;
    outFile.close();

    cout << "Converted file saved to digits_" << filename << endl;
}

void task22() {
    cout << "\n~~~ TASK 22: Split lines by length parity." << endl;

    string filename;
    int N;
    cout << "Enter filename: ";
    cin >> filename;
    cout << "Enter number of lines: ";
    cin >> N;

    ofstream createFile(filename);
    if (!createFile) {
        cout << "Error creating file!" << endl;
        return;
    }

    cin.ignore();
    for (int i = 0; i < N; i++) {
        string line;
        cout << "Enter line " << i + 1 << ": ";
        getline(cin, line);
        createFile << line << endl;
    }
    createFile.close();

    ifstream inFile(filename);
    vector<string> oddLines, evenLines;
    string line;

    while (getline(inFile, line)) {
        if (line.length() % 2 == 0) {
            evenLines.push_back(line);
        }
        else {
            oddLines.push_back(line);
        }
    }
    inFile.close();

    ofstream oddFile("H_" + filename), evenFile("G_" + filename);

    for (const auto& l : oddLines) oddFile << l << endl;
    for (const auto& l : evenLines) evenFile << l << endl;

    oddFile.close();
    evenFile.close();

    cout << "Odd-length lines saved to H_" << filename << endl;
    cout << "Even-length lines saved to G_" << filename << endl;
}

void task23() {
    cout << "\n~~~ TASK 23: Count empty lines and max length." << endl;

    string filename;
    cout << "Enter filename: ";
    cin >> filename;

    ifstream file(filename);
    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }

    int emptyCount = 0, maxLength = 0;
    string line;

    while (getline(file, line)) {
        if (line.empty()) {
            emptyCount++;
        }
        if (line.length() > maxLength) {
            maxLength = line.length();
        }
    }
    file.close();

    cout << "Empty lines: " << emptyCount << endl;
    cout << "Maximum line length: " << maxLength << endl;
}

void task24() {
    cout << "\n~~~ TASK 24: Display lines." << endl;

    string filename;
    cout << "Enter filename: ";
    cin >> filename;

    ifstream file(filename);
    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }

    cout << "\nAll lines:" << endl;
    string line;
    int lineNum = 0;

    while (getline(file, line)) {
        lineNum++;
        cout << lineNum << ": " << line << endl;
    }
    file.close();

    file.open(filename);
    cout << "\nLines with more than 60 characters:" << endl;
    lineNum = 0;

    while (getline(file, line)) {
        lineNum++;
        if (line.length() > 60) {
            cout << lineNum << ": " << line << endl;
        }
    }
    file.close();
}

void task25() {
    cout << "\n~~~ TASK 25: Justify text." << endl;

    string filename;
    cout << "Enter filename: ";
    cin >> filename;

    ifstream inFile(filename);
    if (!inFile) {
        cout << "Error opening file!" << endl;
        return;
    }

    string text, line;
    while (getline(inFile, line)) text += line + " ";
    inFile.close();

    vector<string> words;
    string word;

    for (char c : text) {
        if (isalpha(c)) {
            word += c;
        }
        else if (!word.empty()) {
            words.push_back(word);
            word.clear();
        }
    }

    const int LINE_WIDTH = 60;
    vector<string> lines;
    string currentLine;

    for (const auto& w : words) {
        if (currentLine.length() + w.length() + (currentLine.empty() ? 0 : 1) <= LINE_WIDTH) {
            if (!currentLine.empty()) currentLine += " ";
            currentLine += w;
        }
        else {
            lines.push_back(currentLine);
            currentLine = w;
        }
    }
    if (!currentLine.empty()) lines.push_back(currentLine);

    ofstream outFile("justified_" + filename);
    for (const auto& l : lines) {
        outFile << l << endl;
    }
    outFile.close();

    cout << "Justified text saved to justified_" << filename << endl;
}

void task26() {
    cout << "\n~~~ TASK 26: Transform file." << endl;

    string filename;
    cout << "Enter filename: ";
    cin >> filename;

    ifstream inFile(filename);
    if (!inFile) {
        cout << "Error opening file!" << endl;
        return;
    }

    vector<string> transformedLines;
    string line;

    while (getline(inFile, line)) {
        string transformed;
        for (char c : line) {
            if (c == '0') transformed += '1';
            else if (c == '1') transformed += '0';
            else transformed += c;
        }
        transformedLines.push_back(transformed);
    }
    inFile.close();

    ofstream outFile("G_" + filename);
    for (const auto& l : transformedLines) {
        outFile << l << endl;
    }
    outFile.close();

    cout << "Transformed file saved to G_" << filename << endl;
}

void task27() {
    cout << "\n~~~ TASK 27: Add space to each line." << endl;

    string filename;
    cout << "Enter filename: ";
    cin >> filename;

    ifstream inFile(filename);
    if (!inFile) {
        cout << "Error opening file!" << endl;
        return;
    }

    vector<string> spacedLines;
    string line;

    while (getline(inFile, line)) {
        spacedLines.push_back(" " + line);
    }
    inFile.close();

    ofstream outFile("G_" + filename);
    for (const auto& l : spacedLines) {
        outFile << l << endl;
    }
    outFile.close();

    cout << "Modified file saved to G_" << filename << endl;
}

void task28() {
    cout << "\n~~~ TASK 28: Evaluate Polynomials." << endl;

    string filename;
    double x;
    cout << "Enter filename: ";
    cin >> filename;
    cout << "Enter x value: ";
    cin >> x;

    ifstream inFile(filename);
    if (!inFile) {
        cout << "Error opening file!" << endl;
        return;
    }

    ofstream outFile("polynomial_results.txt");
    string line;
    int lineNum = 0;

    auto power = [](double base, int exp) -> double {
        double result = 1.0;
        for (int i = 0; i < exp; i++) {
            result *= base;
        }
        return result;
        };

    while (getline(inFile, line)) {
        lineNum++;
        try {
            double result = 0.0;
            string expression = line;

            expression.erase(remove(expression.begin(), expression.end(), ' '), expression.end());

            if (expression.empty()) {
                outFile << "Line " << lineNum << ": EMPTY" << endl;
                continue;
            }

            size_t pos = 0;
            string term;
            char lastOp = '+';

            while (pos < expression.length()) {
                size_t nextOp = expression.find_first_of("+-", pos + 1);
                if (nextOp == string::npos) {
                    term = expression.substr(pos);
                    pos = expression.length();
                }
                else {
                    term = expression.substr(pos, nextOp - pos);
                    pos = nextOp;
                }

                if (!term.empty()) {
                    size_t xPos = term.find('x');

                    if (xPos != string::npos) {
                        string coeffStr = term.substr(0, xPos);
                        double coefficient = 1.0;

                        if (!coeffStr.empty()) {
                            if (coeffStr == "+") coefficient = 1.0;
                            else if (coeffStr == "-") coefficient = -1.0;
                            else coefficient = stod(coeffStr);
                        }

                        size_t powerPos = term.find('^', xPos);
                        int powerVal = 1;

                        if (powerPos != string::npos && powerPos + 1 < term.length()) {
                            powerVal = stoi(term.substr(powerPos + 1));
                        }

                        double termValue = coefficient * power(x, powerVal);

                        if (lastOp == '+') result += termValue;
                        else if (lastOp == '-') result -= termValue;

                    }
                    else {
                        double constant = stod(term);

                        if (lastOp == '+') result += constant;
                        else if (lastOp == '-') result -= constant;
                    }
                }

                if (pos < expression.length()) {
                    lastOp = expression[pos];
                    pos++;
                }
            }

            outFile << "Line " << lineNum << ": " << fixed << setprecision(2) << result << endl;

        }
        catch (const exception& e) {
            outFile << "Line " << lineNum << ": INVALID (" << e.what() << ")" << endl;
        }
    }

    inFile.close();
    outFile.close();

    cout << "Polynomial results saved to polynomial_results.txt" << endl;
}

void displayMenu() {
    cout << "~~~ MAIN MENU ~~~" << endl;
    cout << "5. Count Lines with Specific Patterns" << endl;
    cout << "6. Student Average by Group" << endl;
    cout << "7. HTML Tag Validator" << endl;
    cout << "8. Multiplication Game" << endl;
    cout << "9. Game Results (call itogi function)" << endl;
    cout << "10. Remove Lines Multiple of N" << endl;
    cout << "11. Center Align Text" << endl;
    cout << "12. Remove Extra Spaces" << endl;
    cout << "13. Caesar Cipher" << endl;
    cout << "14. Merge Files by Lines" << endl;
    cout << "15. Replace Integers with Binary" << endl;
    cout << "16. Replace Numbers with Log/Exp" << endl;
    cout << "17. Run-Length Encoding" << endl;
    cout << "18. Find Min/Max Line Lengths" << endl;
    cout << "19. Words Starting with Letter" << endl;
    cout << "20. Remove Lines in Range" << endl;
    cout << "21. Replace Digits with English Names" << endl;
    cout << "22. Split Lines by Length Parity" << endl;
    cout << "23. Count Empty Lines and Max Length" << endl;
    cout << "24. Display Lines" << endl;
    cout << "25. Justify Text" << endl;
    cout << "26. Transform File (0/1 swap)" << endl;
    cout << "27. Add Space to Each Line" << endl;
    cout << "28. Evaluate Polynomials" << endl;
    cout << "0. Exit" << endl;
    cout << "~~~" << endl;
    cout << "Enter your choice (0-28): ";
}

int main() {
    int choice;

    do {
        displayMenu();
        cin >> choice;

        try {
            switch (choice) {
            case 5: task5(); break;
            case 6: task6(); break;
            case 7: task7(); break;
            case 8: task8(); break;
            case 9: itogi("game_results.txt"); break;
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
            case 22: task22(); break;
            case 23: task23(); break;
            case 24: task24(); break;
            case 25: task25(); break;
            case 26: task26(); break;
            case 27: task27(); break;
            case 28: task28(); break;
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