#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stack>
#include <stdexcept>

namespace CustomTemplates {

    template<typename T>
    T findMax(const T& a, const T& b) {
        return (a > b) ? a : b;
    }

    template<>
    const char* findMax<const char*>(const char* const& a, const char* const& b) {
        return (std::string(a) > std::string(b)) ? a : b;
    }

    class Rational {
    private:
        int numerator;
        int denominator;

        void reduce() {
            int a = numerator;
            int b = denominator;
            while (b != 0) {
                int temp = b;
                b = a % b;
                a = temp;
            }
            int gcd = a;
            numerator /= gcd;
            denominator /= gcd;

            if (denominator < 0) {
                numerator = -numerator;
                denominator = -denominator;
            }
        }

    public:
        Rational(int num = 0, int den = 1) : numerator(num), denominator(den) {
            if (denominator == 0) {
                throw std::invalid_argument("Denominator cannot be zero");
            }
            reduce();
        }

        bool operator>(const Rational& other) const {
            return (numerator * other.denominator) > (other.numerator * denominator);
        }

        friend std::ostream& operator<<(std::ostream& os, const Rational& rat) {
            os << rat.numerator;
            if (rat.denominator != 1) {
                os << "/" << rat.denominator;
            }
            return os;
        }

        int getNumerator() const { return numerator; }
        int getDenominator() const { return denominator; }
    };

    template<typename T>
    class CustomStack {
    private:
        struct Node {
            T data;
            std::unique_ptr<Node> next;
            Node(const T& value) : data(value), next(nullptr) {}
        };

        std::unique_ptr<Node> topNode;
        size_t stackSize;

    public:
        CustomStack() : topNode(nullptr), stackSize(0) {}

        ~CustomStack() {
            while (!empty()) {
                pop();
            }
        }

        CustomStack(const CustomStack& other) : topNode(nullptr), stackSize(0) {
            if (!other.empty()) {
                std::vector<T> temp;
                auto current = other.topNode.get();
                while (current) {
                    temp.push_back(current->data);
                    current = current->next.get();
                }
                for (auto it = temp.rbegin(); it != temp.rend(); ++it) {
                    push(*it);
                }
            }
        }

        CustomStack& operator=(const CustomStack& other) {
            if (this != &other) {
                while (!empty()) {
                    pop();
                }
                if (!other.empty()) {
                    std::vector<T> temp;
                    auto current = other.topNode.get();
                    while (current) {
                        temp.push_back(current->data);
                        current = current->next.get();
                    }
                    for (auto it = temp.rbegin(); it != temp.rend(); ++it) {
                        push(*it);
                    }
                }
            }
            return *this;
        }

        void push(const T& value) {
            auto newNode = std::make_unique<Node>(value);
            newNode->next = std::move(topNode);
            topNode = std::move(newNode);
            stackSize++;
        }

        void pop() {
            if (empty()) {
                throw std::runtime_error("Stack is empty");
            }
            topNode = std::move(topNode->next);
            stackSize--;
        }

        T& top() {
            if (empty()) {
                throw std::runtime_error("Stack is empty");
            }
            return topNode->data;
        }

        const T& top() const {
            if (empty()) {
                throw std::runtime_error("Stack is empty");
            }
            return topNode->data;
        }

        bool empty() const {
            return topNode == nullptr;
        }

        size_t size() const {
            return stackSize;
        }
    };

    template<typename T>
    size_t readArrayUntilZero(CustomStack<T>& resultStack) {
        T value;
        size_t count = 0;

        std::cout << "Enter numbers (0 to stop):\n";
        while (true) {
            std::cin >> value;
            if (value == T(0)) {
                break;
            }
            resultStack.push(value);
            count++;
        }

        return count;
    }

    template<typename T>
    size_t readArrayUntilZeroSTL(std::stack<T>& resultStack) {
        T value;
        size_t count = 0;

        std::cout << "Enter numbers (0 to stop):\n";
        while (true) {
            std::cin >> value;
            if (value == T(0)) {
                break;
            }
            resultStack.push(value);
            count++;
        }

        return count;
    }

    template<typename T>
    void displayStack(CustomStack<T>& stack) {
        CustomStack<T> temp;

        std::cout << "Stack contents: ";
        while (!stack.empty()) {
            std::cout << stack.top() << " ";
            temp.push(stack.top());
            stack.pop();
        }

        while (!temp.empty()) {
            stack.push(temp.top());
            temp.pop();
        }
        std::cout << "\n";
    }

    template<typename T>
    void displaySTLStack(std::stack<T>& stack) {
        std::stack<T> temp;

        std::cout << "STL Stack contents: ";
        while (!stack.empty()) {
            std::cout << stack.top() << " ";
            temp.push(stack.top());
            stack.pop();
        }

        while (!temp.empty()) {
            stack.push(temp.top());
            temp.pop();
        }
        std::cout << "\n";
    }

}

void demonstrateTask1() {
    using namespace CustomTemplates;

    std::cout << "~~~ Task 1: Template Function FindMax.\n";

    // test with integers
    int a = 10, b = 20;
    std::cout << "Max of " << a << " and " << b << " is: " << findMax(a, b) << "\n";

    // test with doubles
    double x = 3.14, y = 2.71;
    std::cout << "Max of " << x << " and " << y << " is: " << findMax(x, y) << "\n";

    // test with strings
    std::string s1 = "apple", s2 = "banana";
    std::cout << "Max of \"" << s1 << "\" and \"" << s2 << "\" is: \"" << findMax(s1, s2) << "\"\n";

    // test with C-style strings
    const char* str1 = "hello";
    const char* str2 = "world";
    std::cout << "Max of \"" << str1 << "\" and \"" << str2 << "\" is: \"" << findMax(str1, str2) << "\"\n";

    // test with Rational numbers
    try {
        Rational r1(3, 4), r2(2, 3);
        std::cout << "Max of " << r1 << " and " << r2 << " is: " << findMax(r1, r2) << "\n";

        Rational r3(5, 2), r4(7, 3);
        std::cout << "Max of " << r3 << " and " << r4 << " is: " << findMax(r3, r4) << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error with Rational numbers: " << e.what() << "\n";
    }
}

void demonstrateTask2() {
    using namespace CustomTemplates;

    std::cout << "\n~~~ Task 2: Custom Stack Implementation.\n";

    // test with integers using custom stack
    std::cout << "Testing CustomStack with integers:\n";
    CustomStack<int> customIntStack;
    size_t count1 = readArrayUntilZero(customIntStack);
    std::cout << "Read " << count1 << " numbers\n";
    displayStack(customIntStack);

    // test with integers using STL stack
    std::cout << "\nTesting STL stack with integers:\n";
    std::stack<int> stlIntStack;
    size_t count2 = readArrayUntilZeroSTL(stlIntStack);
    std::cout << "Read " << count2 << " numbers\n";
    displaySTLStack(stlIntStack);

    // test with doubles using custom stack
    std::cout << "\nTesting CustomStack with doubles:\n";
    CustomStack<double> customDoubleStack;
    size_t count3 = readArrayUntilZero(customDoubleStack);
    std::cout << "Read " << count3 << " numbers\n";
    displayStack(customDoubleStack);

    // test stack operations
    std::cout << "\nTesting stack operations:\n";
    CustomStack<int> testStack;
    testStack.push(10);
    testStack.push(20);
    testStack.push(30);

    std::cout << "Stack size: " << testStack.size() << "\n";
    std::cout << "Top element: " << testStack.top() << "\n";

    testStack.pop();
    std::cout << "After pop - Top element: " << testStack.top() << "\n";
    std::cout << "Stack size: " << testStack.size() << "\n";

    // test error handling
    std::cout << "\nTesting error handling:\n";
    try {
        CustomStack<int> emptyStack;
        emptyStack.pop();
    }
    catch (const std::exception& e) {
        std::cout << "Caught expected error: " << e.what() << "\n";
    }
}

int main() {
    int choice;

    do {
        std::cout << "\n~~~ MAIN MENU ~~~\n";
        std::cout << "1. Demonstrate Template Function FindMax\n";
        std::cout << "2. Demonstrate Custom Stack Implementation\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: demonstrateTask1(); break;
        case 2: demonstrateTask2(); break;
        case 0: std::cout << "Bye!\n"; break;
        default: std::cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}