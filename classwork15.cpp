#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iomanip>

using namespace std;

string task1_new_string(const string& input) {
    size_t colon_pos = input.find(':');
    if (colon_pos == string::npos) {
        return input;
    }

    size_t comma_pos = input.find(',', colon_pos + 1);
    if (comma_pos == string::npos) {
        return input.substr(colon_pos);
    }

    return input.substr(colon_pos + 1, comma_pos - colon_pos - 1);
}

void task1_replace_string(string& input) {
    size_t colon_pos = input.find(':');
    if (colon_pos == string::npos) {
        return;
    }

    size_t comma_pos = input.find(',', colon_pos + 1);
    if (comma_pos == string::npos) {
        input = input.substr(colon_pos);
    }
    else {
        input = input.substr(colon_pos + 1, comma_pos - colon_pos - 1);
    }
}

string task2_new_string(const string& input) {
    size_t first_dot = input.find('.');
    size_t last_dot = input.rfind('.');

    if (first_dot == string::npos) {
        string result = input;
        size_t start = result.find_first_not_of(" ");
        if (start != string::npos) {
            result = result.substr(start);
        }
        return result;
    }

    if (first_dot == last_dot) {
        return input.substr(first_dot);
    }

    string result = input.substr(0, first_dot) + input.substr(last_dot);
    return result;
}

void task2_replace_string(string& input) {
    size_t first_dot = input.find('.');
    size_t last_dot = input.rfind('.');

    if (first_dot == string::npos) {
        size_t start = input.find_first_not_of(" ");
        if (start != string::npos) {
            input = input.substr(start);
        }
        return;
    }

    if (first_dot == last_dot) {
        input = input.substr(first_dot);
    }
    else {
        input = input.substr(0, first_dot) + input.substr(last_dot);
    }
}

string task3_new_string(const string& input) {
    string result;
    string word;
    bool in_word = false;

    for (char c : input) {
        if (c == ' ') {
            if (in_word) {
                if (!word.empty()) {
                    word.pop_back();
                }
                result += word + " ";
                word.clear();
                in_word = false;
            }
            else {
                result += " ";
            }
        }
        else {
            word += c;
            in_word = true;
        }
    }

    if (in_word && !word.empty()) {
        word.pop_back();
        result += word;
    }

    return result;
}

void task3_replace_string(string& input) {
    string result;
    string word;
    bool in_word = false;

    for (char c : input) {
        if (c == ' ') {
            if (in_word) {
                if (!word.empty()) {
                    word.pop_back();
                }
                result += word + " ";
                word.clear();
                in_word = false;
            }
            else {
                result += " ";
            }
        }
        else {
            word += c;
            in_word = true;
        }
    }

    if (in_word && !word.empty()) {
        word.pop_back();
        result += word;
    }

    input = result;
}

vector<double> task4(const string& input, char separator, int& n) {
    vector<double> result;
    stringstream ss(input);
    string token;

    while (getline(ss, token, separator) && result.size() < n) {
        try {
            double value = stod(token);
            result.push_back(value);
        }
        catch (const exception&) {
            continue;
        }
    }

    n = result.size();
    return result;
}

vector<string> task5(const string& input, char separator, int n) {
    vector<string> result;
    stringstream ss(input);
    string token;

    while (getline(ss, token, separator) && result.size() < n) {
        result.push_back(token);
    }

    return result;
}

void task6(const string& input) {
    vector<string> words;
    stringstream ss(input);
    string word;

    while (ss >> word) {
        words.push_back(word);
    }

    if (words.empty()) {
        cout << "No words found!" << endl;
        return;
    }

    size_t min_length = words[0].length();
    for (const auto& w : words) {
        if (w.length() < min_length) {
            min_length = w.length();
        }
    }

    cout << "Shortest word length: " << min_length << endl;

    cout << "a) First shortest word: ";
    for (const auto& w : words) {
        if (w.length() == min_length) {
            cout << w << endl;
            break;
        }
    }

    cout << "b) Last shortest word: ";
    for (auto it = words.rbegin(); it != words.rend(); ++it) {
        if (it->length() == min_length) {
            cout << *it << endl;
            break;
        }
    }

    cout << "c) All shortest words: ";
    for (const auto& w : words) {
        if (w.length() == min_length) {
            cout << w << " ";
        }
    }
    cout << endl;
}

void task1_demo() {
    cout << "\n~~~ TASK 1: Substring between first colon and next comma." << endl;

    string test1 = "Text before: extract this, and after";
    string test2 = "Text without colon or comma";
    string test3 = "Text with: but no comma after";

    cout << "Test 1 - New string: " << task1_new_string(test1) << endl;

    string test1_copy = test1;
    task1_replace_string(test1_copy);
    cout << "Test 1 - Replace: " << test1_copy << endl;

    cout << "Test 2 - New string: " << task1_new_string(test2) << endl;

    string test3_copy = test3;
    task1_replace_string(test3_copy);
    cout << "Test 3 - Replace: " << test3_copy << endl;
}

void task2_demo() {
    cout << "\n~~~ TASK 2: Remove substring between first and last dot." << endl;

    string test1 = "Start. Remove this. End.";
    string test2 = "No dots here";
    string test3 = "Only one. dot";
    string test4 = "   Spaces at start";

    cout << "Test 1 - New string: " << task2_new_string(test1) << endl;

    string test1_copy = test1;
    task2_replace_string(test1_copy);
    cout << "Test 1 - Replace: " << test1_copy << endl;

    cout << "Test 2 - New string: " << task2_new_string(test2) << endl;

    string test4_copy = test4;
    task2_replace_string(test4_copy);
    cout << "Test 4 - Replace: " << test4_copy << endl;
}

void task3_demo() {
    cout << "\n~~~ TASK 3: Remove last letter from each word." << endl;

    string test1 = "Hello world test";
    string test2 = "Single";
    string test3 = "Multiple   spaces   between";

    cout << "Test 1 - New string: " << task3_new_string(test1) << endl;

    string test1_copy = test1;
    task3_replace_string(test1_copy);
    cout << "Test 1 - Replace: " << test1_copy << endl;

    cout << "Test 2 - New string: " << task3_new_string(test2) << endl;

    string test3_copy = test3;
    task3_replace_string(test3_copy);
    cout << "Test 3 - Replace: " << test3_copy << endl;
}

void task4_demo() {
    cout << "\n~~~ TASK 4: Extract first n real numbers." << endl;

    string test1 = "12.5;23.7;abc;45.1;67.8";
    int n = 3;

    vector<double> numbers = task4(test1, ';', n);

    cout << "Extracted " << n << " numbers: ";
    for (double num : numbers) {
        cout << num << " ";
    }
    cout << endl;
}

void task5_demo() {
    cout << "\n~~~ TASK 5: Extract first n words." << endl;

    string test1 = "apple,banana,cherry,date,elderberry";
    int n = 3;

    vector<string> words = task5(test1, ',', n);

    cout << "First " << n << " words: ";
    for (const auto& word : words) {
        cout << word << " ";
    }
    cout << endl;
}

void task6_demo() {
    cout << "\n~~~ TASK 6: Find shortest word." << endl;

    string test1 = "The quick brown fox jumps over the lazy dog";
    string test2 = "cat dog elephant mouse";
    string test3 = "a bb ccc dd e";

    cout << "Test 1:" << endl;
    task6(test1);

    cout << "\nTest 2:" << endl;
    task6(test2);

    cout << "\nTest 3:" << endl;
    task6(test3);
}

void displayMenu() {
    cout << "~~~ MAIN MENU ~~~" << endl;
    cout << "1. Substring between colon and comma" << endl;
    cout << "2. Remove between first and last dot" << endl;
    cout << "3. Remove last letter from words" << endl;
    cout << "4. Extract real numbers" << endl;
    cout << "5. Extract first n words" << endl;
    cout << "6. Find shortest word" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter your choice (0-6): ";
}

int main() {
    int choice;

    do {
        displayMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: task1_demo(); break;
        case 2: task2_demo(); break;
        case 3: task3_demo(); break;
        case 4: task4_demo(); break;
        case 5: task5_demo(); break;
        case 6: task6_demo(); break;
        case 0: cout << "Bye!" << endl; break;
        default: cout << "Invalid choice!" << endl; break;
        }

        if (choice != 0) {
            cout << "\nPress Enter to continue...";
            cin.get();
        }

    } while (choice != 0);

    return 0;
}