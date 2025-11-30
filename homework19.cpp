#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

void task17() {
    cout << "TASK 17: List Modification.\n";

    list<int> lst;
    int n, value;

    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter " << n << " elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> value;
        lst.push_back(value);
    }

    cout << "Original list: ";
    for (auto it = lst.begin(); it != lst.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;

    auto it = lst.begin();
    while (it != lst.end()) {
        if (*it != 0) {
            lst.insert(it, -1);
        }
        it++;
    }

    it = lst.begin();
    while (it != lst.end()) {
        if (*it == 0) {
            it++;
            lst.insert(it, 2);
        }
        else {
            it++;
        }
    }

    cout << "Modified list: ";
    for (auto it = lst.begin(); it != lst.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
}

void testTask17() {
    cout << "\n Test for task 17.\n";

    list<int> test1 = { 1, 0, 3, 0, 5 };
    cout << "Test 1 - Input: 1 0 3 0 5\n";

    auto it = test1.begin();
    while (it != test1.end()) {
        if (*it != 0) {
            test1.insert(it, -1);
        }
        it++;
    }

    it = test1.begin();
    while (it != test1.end()) {
        if (*it == 0) {
            it++;
            test1.insert(it, 2);
        }
        else {
            it++;
        }
    }

    cout << "Expected: -1 1 0 2 -1 3 0 2 -1 5\n";
    cout << "Actual:   ";
    for (int x : test1) cout << x << " ";
    cout << endl;

    list<int> test2 = { 0, 0, 1, 2, 0 };
    cout << "\nTest 2 - Input: 0 0 1 2 0\n";

    it = test2.begin();
    while (it != test2.end()) {
        if (*it != 0) {
            test2.insert(it, -1);
        }
        it++;
    }

    it = test2.begin();
    while (it != test2.end()) {
        if (*it == 0) {
            it++;
            test2.insert(it, 2);
        }
        else {
            it++;
        }
    }

    cout << "Expected: 0 2 0 2 -1 1 -1 2 0 2\n";
    cout << "Actual:   ";
    for (int x : test2) cout << x << " ";
    cout << endl;
}

int main() {
    int choice;

    while (true) {
        cout << "\n~~~ MAIN MENU ~~~\n";
        cout << "1. Run Task 17 (custom input)\n";
        cout << "2. Test Task 17 (predefined tests)\n";
        cout << "3. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        switch (choice) {
        case 1: task17(); break;
        case 2: testTask17(); break;
        case 3: return 0;
        default: cout << "Invalid choice!\n";
        }
    }

    return 0;
}