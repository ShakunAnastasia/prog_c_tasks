#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <set>
#include <iterator>

using namespace std;

void task9() {
    cout << "~~~ TASK 9: vector elements containment ~~~\n";

    vector<int> V0;
    int n, m, value;

    cout << "Enter size of vector V0: ";
    cin >> n;
    cout << "Enter " << n << " elements for V0:\n";
    for (int i = 0; i < n; i++) {
        cin >> value;
        V0.push_back(value);
    }

    cout << "Enter number of vectors N: ";
    cin >> m;

    vector<vector<int>> vectors(m);
    for (int i = 0; i < m; i++) {
        int size;
        cout << "Enter size of vector V" << i + 1 << ": ";
        cin >> size;
        cout << "Enter " << size << " elements for V" << i + 1 << ":\n";
        for (int j = 0; j < size; j++) {
            cin >> value;
            vectors[i].push_back(value);
        }
    }

    cout << "\nVectors that contain all elements of V0:\n";
    int count = 0;

    for (int i = 0; i < m; i++) {
        vector<int> temp = vectors[i];
        bool contains_all = true;

        for (int elem : V0) {
            auto it = find(temp.begin(), temp.end(), elem);
            if (it == temp.end()) {
                contains_all = false;
                break;
            }
            else {
                temp.erase(it);
            }
        }

        if (contains_all) {
            cout << "Vector V" << i + 1 << ": ";
            for (int val : vectors[i]) {
                cout << val << " ";
            }
            cout << endl;
            count++;
        }
    }

    cout << "Total vectors containing all elements of V0: " << count << endl;
}

void task11() {
    cout << "\n~~~ TASK 11: common words in files ~~~\n";

    string filename1, filename2;
    cout << "Enter first filename: ";
    cin >> filename1;
    cout << "Enter second filename: ";
    cin >> filename2;

    ifstream file1(filename1);
    ifstream file2(filename2);

    if (!file1.is_open() || !file2.is_open()) {
        cout << "Error opening files!\n";
        return;
    }

    set<string> words1, words2;
    string word;

    while (file1 >> word) {
        words1.insert(word);
    }
    while (file2 >> word) {
        words2.insert(word);
    }

    file1.close();
    file2.close();

    set<string> common_words;
    set_intersection(words1.begin(), words1.end(),
        words2.begin(), words2.end(),
        inserter(common_words, common_words.begin()));

    set<string> different_words;
    set_symmetric_difference(words1.begin(), words1.end(),
        words2.begin(), words2.end(),
        inserter(different_words, different_words.begin()));

    cout << "\nCommon words in both files:\n";
    if (common_words.empty()) {
        cout << "No common words found.\n";
    }
    else {
        for (const string& w : common_words) {
            cout << w << " ";
        }
        cout << endl;
    }

    cout << "\nWords that are not common (different):\n";
    if (different_words.empty()) {
        cout << "No different words found.\n";
    }
    else {
        for (const string& w : different_words) {
            cout << w << " ";
        }
        cout << endl;
    }
}

void testTask9() {
    cout << "\n~ Test task 9 ~\n";

    vector<int> V0 = { 1, 2, 2 };
    vector<vector<int>> vectors = {
        {1, 2, 3, 4, 5},
        {1, 2, 2, 3, 4},
        {2, 2, 1, 5, 6},
        {1, 1, 2, 3, 4}
    };

    cout << "V0 = ";
    for (int val : V0) cout << val << " ";
    cout << endl;

    int count = 0;
    for (int i = 0; i < vectors.size(); i++) {
        vector<int> temp = vectors[i];
        bool contains_all = true;

        for (int elem : V0) {
            auto it = find(temp.begin(), temp.end(), elem);
            if (it == temp.end()) {
                contains_all = false;
                break;
            }
            else {
                temp.erase(it);
            }
        }

        if (contains_all) {
            cout << "Vector " << i + 1 << " contains all elements of V0\n";
            count++;
        }
    }
    cout << "Total: " << count << " vectors\n";
}

void testTask11() {
    cout << "\n~ Test task 11 ~\n";

    ofstream file1("test1.txt");
    ofstream file2("test2.txt");

    file1 << "apple banana cherry date apple";
    file2 << "banana cherry elderberry fig";

    file1.close();
    file2.close();

    cout << "Created test files: test1.txt and test2.txt\n";

    ifstream f1("test1.txt");
    ifstream f2("test2.txt");

    set<string> words1, words2;
    string word;

    while (f1 >> word) words1.insert(word);
    while (f2 >> word) words2.insert(word);

    f1.close();
    f2.close();

    set<string> common, different;

    set_intersection(words1.begin(), words1.end(),
        words2.begin(), words2.end(),
        inserter(common, common.begin()));

    set_symmetric_difference(words1.begin(), words1.end(),
        words2.begin(), words2.end(),
        inserter(different, different.begin()));

    cout << "Expected common words: banana cherry\n";
    cout << "Actual common words: ";
    for (const string& w : common) cout << w << " ";
    cout << endl;

    cout << "Expected different words: apple date elderberry fig\n";
    cout << "Actual different words: ";
    for (const string& w : different) cout << w << " ";
    cout << endl;
}

int main() {
    int choice;

    while (true) {
        cout << "\n~~~ MAIN MENU ~~~\n";
        cout << "1. Task 9 - Vector Containment\n";
        cout << "2. Task 11 - Common Words\n";
        cout << "3. Test Task 9\n";
        cout << "4. Test Task 11\n";
        cout << "5. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        switch (choice) {
        case 1: task9(); break;
        case 2: task11(); break;
        case 3: testTask9(); break;
        case 4: testTask11(); break;
        case 5: return 0;
        default: cout << "Invalid choice!\n";
        }
    }

    return 0;
}