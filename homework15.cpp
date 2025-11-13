#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cctype>
#include <map>
#include <set>
#include <functional>
#include <stdexcept>
#include <iomanip>
#include <regex>

using namespace std;

class StringProcessor {
private:
    string text;

    void validateNotEmpty() const {
        if (text.empty()) {
            throw invalid_argument("Text cannot be empty");
        }
    }

    vector<string> splitWords() const {
        vector<string> words;
        string currentWord;

        for (char c : text + ' ') {
            if (isalpha(c)) {
                currentWord += c;
            }
            else {
                if (!currentWord.empty()) {
                    words.push_back(currentWord);
                    currentWord.clear();
                }
            }
        }

        return words;
    }

    bool isValidDate(int day, int month, int year) const {
        if (month < 1 || month > 12) return false;
        if (day < 1) return false;
        int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

        if (month == 2) {
            bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
            if (isLeapYear) daysInMonth[1] = 29;
        }

        return day <= daysInMonth[month - 1];
    }

public:
    StringProcessor() = default;

    explicit StringProcessor(const string& input) : text(input) {}

    void setText(const string& input) {
        if (input.length() > 10000) {
            throw invalid_argument("Text is too long");
        }
        text = input;
    }

    const string& getText() const { return text; }

    // Task 7
    string replaceSpacesWithCommas() const {
        validateNotEmpty();

        string result;
        string currentWord;

        for (char c : text) {
            if (isalpha(c)) {
                currentWord += c;
            }
            else if (isspace(c)) {
                if (!currentWord.empty()) {
                    if (!result.empty()) {
                        result += ",";
                    }
                    result += currentWord;
                    currentWord.clear();
                }
            }
        }

        if (!currentWord.empty()) {
            if (!result.empty()) {
                result += ",";
            }
            result += currentWord;
        }

        if (!result.empty()) {
            result += ".";
        }

        return result;
    }

    // Task 8
    string removeLastLetterFromWords() const {
        validateNotEmpty();

        string result;
        string currentWord;

        for (char c : text) {
            if (isalpha(c)) {
                currentWord += c;
            }
            else {
                if (!currentWord.empty()) {
                    if (currentWord.length() > 1) {
                        result += currentWord.substr(0, currentWord.length() - 1);
                    }
                    else {
                        result += currentWord;
                    }
                    currentWord.clear();
                }
                result += c;
            }
        }

        if (!currentWord.empty()) {
            if (currentWord.length() > 1) {
                result += currentWord.substr(0, currentWord.length() - 1);
            }
            else {
                result += currentWord;
            }
        }

        return result;
    }

    // Task 9
    vector<string> findWordsEndingWith(char endingChar) const {
        validateNotEmpty();

        vector<string> result;
        string currentWord;

        for (char c : text + ' ') {
            if (isalpha(c)) {
                currentWord += c;
            }
            else {
                if (!currentWord.empty() &&
                    tolower(currentWord.back()) == tolower(endingChar)) {
                    result.push_back(currentWord);
                }
                currentWord.clear();
            }
        }

        return result;
    }

    // Task 10
    int countWordsSameStartEnd() const {
        validateNotEmpty();

        int count = 0;
        string currentWord;

        for (char c : text + ' ') {
            if (isalpha(c)) {
                currentWord += tolower(c);
            }
            else {
                if (!currentWord.empty() && currentWord.length() > 1 &&
                    currentWord.front() == currentWord.back()) {
                    count++;
                }
                currentWord.clear();
            }
        }

        return count;
    }

    // Task 11
    string removeCharacterFromWords(char charToRemove) const {
        validateNotEmpty();

        string result;
        string currentWord;

        for (char c : text) {
            if (isalpha(c)) {
                if (tolower(c) != tolower(charToRemove)) {
                    currentWord += c;
                }
            }
            else {
                if (!currentWord.empty()) {
                    result += currentWord;
                    currentWord.clear();
                }
                result += c;
            }
        }

        if (!currentWord.empty()) {
            result += currentWord;
        }

        return result;
    }

    // Task 12
    string capitalizeWords() const {
        validateNotEmpty();

        string result;
        bool newWord = true;

        for (char c : text) {
            if (isalpha(c)) {
                if (newWord) {
                    result += toupper(c);
                    newWord = false;
                }
                else {
                    result += c;
                }
            }
            else {
                result += c;
                newWord = true;
            }
        }

        return result;
    }

    // Task 13
    vector<string> findLongestWords() const {
        validateNotEmpty();

        auto words = splitWords();
        if (words.empty()) {
            throw runtime_error("No words found");
        }

        size_t maxLength = 0;
        for (const auto& word : words) {
            maxLength = max(maxLength, word.length());
        }

        vector<string> longestWords;
        for (const auto& word : words) {
            if (word.length() == maxLength) {
                longestWords.push_back(word);
            }
        }

        return longestWords;
    }

    // Task 14
    pair<int, int> countWordAndSubstringOccurrences(const string& targetWord,
        const string& substring) const {
        validateNotEmpty();

        if (targetWord.empty() || substring.empty()) {
            throw invalid_argument("Word and substring cannot be empty");
        }

        int wordCount = 0;
        string currentWord;
        string lowerTarget = targetWord;
        transform(lowerTarget.begin(), lowerTarget.end(), lowerTarget.begin(), ::tolower);

        for (char c : text + ' ') {
            if (isalpha(c)) {
                currentWord += tolower(c);
            }
            else {
                if (!currentWord.empty() && currentWord == lowerTarget) {
                    wordCount++;
                }
                currentWord.clear();
            }
        }

        int substringCount = 0;
        string lowerText = text;
        transform(lowerText.begin(), lowerText.end(), lowerText.begin(), ::tolower);
        string lowerSubstring = substring;
        transform(lowerSubstring.begin(), lowerSubstring.end(), lowerSubstring.begin(), ::tolower);

        size_t pos = 0;
        while ((pos = lowerText.find(lowerSubstring, pos)) != string::npos) {
            substringCount++;
            pos += lowerSubstring.length();
        }

        return make_pair(wordCount, substringCount);
    }

    // Task 15
    int countWordsContainingCharacter(char character) const {
        validateNotEmpty();

        int count = 0;
        string currentWord;
        char lowerChar = tolower(character);

        for (char c : text + ' ') {
            if (isalpha(c)) {
                currentWord += tolower(c);
            }
            else {
                if (!currentWord.empty() && currentWord.find(lowerChar) != string::npos) {
                    count++;
                }
                currentWord.clear();
            }
        }

        return count;
    }

    // Task 16
    vector<string> getWordsEndingWith(char endingChar) const {
        return findWordsEndingWith(endingChar);
    }

    // Task 17
    string fixArticlesCase() const {
        validateNotEmpty();

        vector<string> words;
        istringstream iss(text);
        string word;

        while (iss >> word) {
            words.push_back(word);
        }

        for (size_t i = 1; i < words.size(); ++i) {
            string prevWord = words[i - 1];
            transform(prevWord.begin(), prevWord.end(), prevWord.begin(), ::tolower);

            if (prevWord == "a" || prevWord == "an" || prevWord == "the") {
                if (!words[i].empty()) {
                    words[i][0] = tolower(words[i][0]);
                }
            }
        }

        string result;
        for (size_t i = 0; i < words.size(); ++i) {
            if (i > 0) result += " ";
            result += words[i];
        }

        return result;
    }

    // Task 18
    double percentageWordsWithDoubleConsonants() const {
        validateNotEmpty();

        auto words = splitWords();
        if (words.empty()) return 0.0;

        int count = 0;
        const string consonants = "bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ";

        for (const auto& word : words) {
            bool hasDoubleConsonant = false;
            for (size_t i = 0; i < word.length() - 1; ++i) {
                if (consonants.find(word[i]) != string::npos &&
                    word[i] == word[i + 1]) {
                    hasDoubleConsonant = true;
                    break;
                }
            }
            if (hasDoubleConsonant) {
                count++;
            }
        }

        return (static_cast<double>(count) / words.size()) * 100.0;
    }

    // Task 19
    vector<string> findParticiples() const {
        validateNotEmpty();

        vector<string> participles;
        string currentWord;

        for (char c : text + ' ') {
            if (isalpha(c)) {
                currentWord += c;
            }
            else {
                if (!currentWord.empty() && currentWord.length() >= 4) {
                    string ending = currentWord.substr(currentWord.length() - 4);
                    transform(ending.begin(), ending.end(), ending.begin(), ::tolower);
                    if (ending == "ings") {
                        participles.push_back(currentWord);
                    }
                }
                currentWord.clear();
            }
        }

        return participles;
    }

    // Task 20
    string shiftLetters() const {
        validateNotEmpty();

        string result = text;

        for (char& c : result) {
            if (isalpha(c)) {
                if (c == 'z') c = 'a';
                else if (c == 'Z') c = 'A';
                else c = c + 1;
            }
        }

        return result;
    }

    // Task 21
    string replaceNumberWordsWithDigits() const {
        validateNotEmpty();

        map<string, char> numberMap = {
            {"one", '1'}, {"two", '2'}, {"three", '3'}, {"four", '4'}, {"five", '5'},
            {"six", '6'}, {"seven", '7'}, {"eight", '8'}, {"nine", '9'}
        };

        string result;
        string currentWord;

        for (char c : text) {
            if (isalpha(c)) {
                currentWord += tolower(c);
            }
            else {
                if (!currentWord.empty()) {
                    auto it = numberMap.find(currentWord);
                    if (it != numberMap.end()) {
                        result += it->second;
                    }
                    else {
                        result += currentWord;
                    }
                    currentWord.clear();
                }
                result += c;
            }
        }

        if (!currentWord.empty()) {
            auto it = numberMap.find(currentWord);
            if (it != numberMap.end()) {
                result += it->second;
            }
            else {
                result += currentWord;
            }
        }

        return result;
    }

    // Task 22
    string removeSecondLastLetter() const {
        validateNotEmpty();

        string result;
        string currentWord;

        for (char c : text) {
            if (isalpha(c)) {
                currentWord += c;
            }
            else {
                if (!currentWord.empty()) {
                    if (currentWord.length() > 2) {
                        string modifiedWord = currentWord;
                        modifiedWord.erase(modifiedWord.length() - 2, 1);
                        result += modifiedWord;
                    }
                    else {
                        result += currentWord;
                    }
                    currentWord.clear();
                }
                result += c;
            }
        }

        if (!currentWord.empty()) {
            if (currentWord.length() > 2) {
                string modifiedWord = currentWord;
                modifiedWord.erase(modifiedWord.length() - 2, 1);
                result += modifiedWord;
            }
            else {
                result += currentWord;
            }
        }

        return result;
    }

    // Task 23
    string transformPossessive() const {
        validateNotEmpty();

        string result = text;
        regex pattern(R"(\b(\w+)'s\s+(\w+)\b)");

        return regex_replace(result, pattern, "$2 of $1");
    }

    // Task 24
    map<string, double> calculateWordPercentage() const {
        validateNotEmpty();

        auto words = splitWords();
        map<string, double> percentages;

        int totalChars = 0;
        for (const auto& word : words) {
            totalChars += word.length();
        }

        if (totalChars > 0) {
            for (const auto& word : words) {
                double percentage = (static_cast<double>(word.length()) / totalChars) * 100.0;
                percentages[word] = percentage;
            }
        }

        return percentages;
    }

    // Task 25
    char findMostCommonVowel() const {
        validateNotEmpty();

        const string vowels = "aeiouyAEIOUY";
        map<char, int> vowelCount;

        for (char c : text) {
            if (vowels.find(c) != string::npos) {
                char lowerVowel = tolower(c);
                vowelCount[lowerVowel]++;
            }
        }

        if (vowelCount.empty()) {
            throw runtime_error("No vowels found");
        }

        auto mostCommon = max_element(vowelCount.begin(), vowelCount.end(),
            [](const pair<char, int>& a, const pair<char, int>& b) {
                return a.second < b.second;
            });

        return mostCommon->first;
    }

    // Task 25.2
    vector<pair<string, string>> convertAndValidateDates() const {
        validateNotEmpty();

        vector<pair<string, string>> results;
        string currentWord;

        for (char c : text + ' ') {
            if (isdigit(c)) {
                currentWord += c;
            }
            else {
                if (!currentWord.empty() && currentWord.length() == 8) {
                    bool allDigits = true;
                    for (char digit : currentWord) {
                        if (!isdigit(digit)) {
                            allDigits = false;
                            break;
                        }
                    }

                    if (allDigits) {
                        int day = stoi(currentWord.substr(0, 2));
                        int month = stoi(currentWord.substr(2, 2));
                        int year = stoi(currentWord.substr(4, 4));

                        string dateFormat = currentWord.substr(0, 2) + "-" +
                            currentWord.substr(2, 2) + "-" +
                            currentWord.substr(4, 4);

                        string status = isValidDate(day, month, year) ? "VALID" : "INVALID";

                        results.push_back(make_pair(dateFormat, status));
                    }
                }
                currentWord.clear();
            }
        }

        return results;
    }
};

string inputText(const string& prompt) {
    string text;
    cout << prompt;
    getline(cin, text);

    if (text.empty()) {
        throw invalid_argument("Input text cannot be empty");
    }

    return text;
}

char inputChar(const string& prompt) {
    string input;
    cout << prompt;
    getline(cin, input);

    if (input.empty()) {
        throw invalid_argument("Input character cannot be empty");
    }

    return input[0];
}

void task7() {
    cout << "~~~ TASK 7: Replace spaces with commas and period.\n";
    try {
        string text = inputText("Enter text: ");
        StringProcessor processor(text);
        string result = processor.replaceSpacesWithCommas();
        cout << "Result: " << result << endl;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

void task8() {
    cout << "~~~ TASK 8: Remove last letter from words.\n";
    try {
        string text = inputText("Enter text: ");
        StringProcessor processor(text);
        string result = processor.removeLastLetterFromWords();
        cout << "Result: " << result << endl;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

void task9() {
    cout << "~~~ TASK 9: Find words ending with character.\n";
    try {
        string text = inputText("Enter text: ");
        char endingChar = inputChar("Enter ending character: ");
        StringProcessor processor(text);
        auto words = processor.findWordsEndingWith(endingChar);

        cout << "Words ending with '" << endingChar << "':\n";
        for (const auto& word : words) {
            cout << word << endl;
        }
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

void task10() {
    cout << "~~~ TASK 10: Count words with same start and end letter.\n";
    try {
        string text = inputText("Enter text: ");
        StringProcessor processor(text);
        int count = processor.countWordsSameStartEnd();
        cout << "Number of words with same start and end letter: " << count << endl;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

void task11() {
    cout << "~~~ TASK 11: Remove character from words.\n";
    try {
        string text = inputText("Enter text: ");
        char charToRemove = inputChar("Enter character to remove: ");
        StringProcessor processor(text);
        string result = processor.removeCharacterFromWords(charToRemove);
        cout << "Result: " << result << endl;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

void task12() {
    cout << "~~~ TASK 12: Capitalize words.\n";
    try {
        string text = inputText("Enter text: ");
        StringProcessor processor(text);
        string result = processor.capitalizeWords();
        cout << "Result: " << result << endl;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

void task13() {
    cout << "~~~ TASK 13: Find all longest words.\n";
    try {
        string text = inputText("Enter text: ");
        StringProcessor processor(text);
        auto longestWords = processor.findLongestWords();

        cout << "Longest words:\n";
        for (const auto& word : longestWords) {
            cout << "'" << word << "' (length: " << word.length() << ")\n";
        }
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

void task14() {
    cout << "~~~ TASK 14: Count word and substring occurrences.\n";
    try {
        string text = inputText("Enter text: ");
        string targetWord = inputText("Enter target word: ");
        string substring = inputText("Enter substring: ");

        StringProcessor processor(text);
        auto counts = processor.countWordAndSubstringOccurrences(targetWord, substring);

        cout << "Word '" << targetWord << "' appears " << counts.first << " times\n";
        cout << "Substring '" << substring << "' appears " << counts.second << " times\n";
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

void task15() {
    cout << "~~~ TASK 15: Count words containing character.\n";
    try {
        string text = inputText("Enter text: ");
        char character = inputChar("Enter character: ");
        StringProcessor processor(text);
        int count = processor.countWordsContainingCharacter(character);
        cout << "Number of words containing '" << character << "': " << count << endl;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

void task16() {
    cout << "~~~ TASK 16: Get words ending with character.\n";
    try {
        string text = inputText("Enter text: ");
        char endingChar = inputChar("Enter ending character: ");
        StringProcessor processor(text);
        auto words = processor.getWordsEndingWith(endingChar);

        cout << "Words ending with '" << endingChar << "':\n";
        for (const auto& word : words) {
            cout << word << endl;
        }
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

void task17() {
    cout << "~~~ TASK 17: Fix case after articles.\n";
    try {
        string text = inputText("Enter text: ");
        StringProcessor processor(text);
        string result = processor.fixArticlesCase();
        cout << "Result: " << result << endl;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

void task18() {
    cout << "~~~ TASK 18: Percentage of words with double consonants.\n";
    try {
        string text = inputText("Enter text: ");
        StringProcessor processor(text);
        double percentage = processor.percentageWordsWithDoubleConsonants();
        cout << "Percentage of words with double consonants: "
            << fixed << setprecision(2) << percentage << "%" << endl;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

void task19() {
    cout << "~~~ TASK 19: Find participles.\n";
    try {
        string text = inputText("Enter text: ");
        StringProcessor processor(text);
        auto participles = processor.findParticiples();

        cout << "Participles found:\n";
        for (const auto& participle : participles) {
            cout << participle << endl;
        }
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

void task20() {
    cout << "~~~ TASK 20: Shift letters.\n";
    try {
        string text = inputText("Enter text: ");
        StringProcessor processor(text);
        string result = processor.shiftLetters();
        cout << "Result: " << result << endl;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

void task21() {
    cout << "~~~ TASK 21: Replace number words with digits.\n";
    try {
        string text = inputText("Enter text: ");
        StringProcessor processor(text);
        string result = processor.replaceNumberWordsWithDigits();
        cout << "Result: " << result << endl;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

void task22() {
    cout << "~~~ TASK 22: Remove second last letter.\n";
    try {
        string text = inputText("Enter text: ");
        StringProcessor processor(text);
        string result = processor.removeSecondLastLetter();
        cout << "Result: " << result << endl;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

void task23() {
    cout << "~~~ TASK 23: Transform possessive form.\n";
    try {
        string text = inputText("Enter text: ");
        StringProcessor processor(text);
        string result = processor.transformPossessive();
        cout << "Result: " << result << endl;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

void task24() {
    cout << "~~~ TASK 24: Word character percentage.\n";
    try {
        string text = inputText("Enter text: ");
        StringProcessor processor(text);
        auto percentages = processor.calculateWordPercentage();

        cout << "Word character percentages:\n";
        for (const auto& pair : percentages) {
            cout << "'" << pair.first << "': " << fixed << setprecision(2)
                << pair.second << "%\n";
        }
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

void task25() {
    cout << "~~~ TASK 25: Find most common vowel.\n";
    try {
        string text = inputText("Enter text: ");
        StringProcessor processor(text);
        char mostCommonVowel = processor.findMostCommonVowel();
        cout << "Most common vowel: '" << mostCommonVowel << "'" << endl;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

void task25_2() {
    cout << "~~~ TASK 25.2: Convert 8-digit words to date format and validate.\n";
    try {
        string text = inputText("Enter text containing 8-digit sequences: ");
        StringProcessor processor(text);
        auto dateResults = processor.convertAndValidateDates();

        if (dateResults.empty()) {
            cout << "No 8-digit sequences found in the text." << endl;
        }
        else {
            cout << "Date conversions and validations:\n";
            for (const auto& result : dateResults) {
                cout << result.first << " - " << result.second << endl;
            }
        }
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

void displayMenu() {
    cout << "~~~ MAIN MENU ~~~" << endl;
    cout << "7. Replace spaces with commas and period" << endl;
    cout << "8. Remove last letter from words" << endl;
    cout << "9. Find words ending with character" << endl;
    cout << "10. Count words with same start and end letter" << endl;
    cout << "11. Remove character from words" << endl;
    cout << "12. Capitalize words" << endl;
    cout << "13. Find all longest words" << endl;
    cout << "14. Count word and substring occurrences" << endl;
    cout << "15. Count words containing character" << endl;
    cout << "16. Get words ending with character" << endl;
    cout << "17. Fix case after articles" << endl;
    cout << "18. Percentage of words with double consonants" << endl;
    cout << "19. Find participles" << endl;
    cout << "20. Shift letters" << endl;
    cout << "21. Replace number words with digits" << endl;
    cout << "22. Remove second last letter" << endl;
    cout << "23. Transform possessive form" << endl;
    cout << "24. Word character percentage" << endl;
    cout << "25. Find most common vowel" << endl;
    cout << "26. Convert 8-digit words to date format" << endl;
    cout << "0. Exit" << endl;
    cout << "~~~" << endl;
    cout << "Enter your choice (0, 7-26): ";
}

int main() {
    int choice;

    do {
        displayMenu();
        cin >> choice;
        cin.ignore();

        try {
            switch (choice) {
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
            case 22: task22(); break;
            case 23: task23(); break;
            case 24: task24(); break;
            case 25: task25(); break;
            case 26: task25_2(); break;
            case 0: cout << "Bye!" << endl; break;
            default: cout << "Invalid choice!" << endl; break;
            }
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }

        if (choice != 0) {
            cout << "\nPress Enter to continue...";
            cin.get();
        }

    } while (choice != 0);

    return 0;
}