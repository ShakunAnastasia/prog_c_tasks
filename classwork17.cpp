#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

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

    int getNumerator() const { return numerator; }
    int getDenominator() const { return denominator; }

    void setNumerator(int num) {
        numerator = num;
        reduce();
    }

    void setDenominator(int den) {
        if (den == 0) {
            throw std::invalid_argument("Denominator cannot be zero");
        }
        denominator = den;
        reduce();
    }

    friend std::ostream& operator<<(std::ostream& os, const Rational& rat) {
        os << rat.numerator;
        if (rat.denominator != 1) {
            os << "/" << rat.denominator;
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Rational& rat) {
        int num, den = 1;
        char slash;

        is >> num;
        if (is.peek() == '/') {
            is >> slash >> den;
        }

        if (den == 0) {
            throw std::invalid_argument("Denominator cannot be zero");
        }

        rat = Rational(num, den);
        return is;
    }

    Rational operator+(const Rational& other) const {
        return Rational(numerator * other.denominator + other.numerator * denominator,
            denominator * other.denominator);
    }

    Rational operator-(const Rational& other) const {
        return Rational(numerator * other.denominator - other.numerator * denominator,
            denominator * other.denominator);
    }

    Rational operator-() const {
        return Rational(-numerator, denominator);
    }

    Rational operator*(const Rational& other) const {
        return Rational(numerator * other.numerator, denominator * other.denominator);
    }

    Rational operator/(const Rational& other) const {
        if (other.numerator == 0) {
            throw std::invalid_argument("Division by zero");
        }
        return Rational(numerator * other.denominator, denominator * other.numerator);
    }

    friend void writeToFile(const Rational& rat, const std::string& filename) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file: " + filename);
        }
        file << rat;
        file.close();
    }
};

class Person {
protected:
    std::string fullName;
    std::string gender;
    int age;

public:
    Person(const std::string& name = "", const std::string& gen = "", int a = 0)
        : fullName(name), gender(gen), age(a) {
    }

    virtual ~Person() = default;

    virtual void input() {
        std::cout << "Enter full name: ";
        std::getline(std::cin, fullName);
        std::cout << "Enter gender: ";
        std::getline(std::cin, gender);
        std::cout << "Enter age: ";
        std::cin >> age;
        std::cin.ignore();
    }

    virtual void output() const {
        std::cout << "Full Name: " << fullName << "\n";
        std::cout << "Gender: " << gender << "\n";
        std::cout << "Age: " << age << "\n";
    }

    virtual std::string getUniversity() const {
        return "";
    }

    virtual std::string getType() const {
        return "Person";
    }
};

class Student : virtual public Person {
protected:
    int course;
    std::string group;
    std::string studentUniversity;

public:
    Student(const std::string& name = "", const std::string& gen = "", int a = 0,
        int c = 1, const std::string& grp = "", const std::string& uni = "")
        : Person(name, gen, a), course(c), group(grp), studentUniversity(uni) {
    }

    void input() override {
        Person::input();
        std::cout << "Enter course: ";
        std::cin >> course;
        std::cin.ignore();
        std::cout << "Enter group: ";
        std::getline(std::cin, group);
        std::cout << "Enter university: ";
        std::getline(std::cin, studentUniversity);
    }

    void output() const override {
        Person::output();
        std::cout << "Course: " << course << "\n";
        std::cout << "Group: " << group << "\n";
        std::cout << "University: " << studentUniversity << "\n";
    }

    std::string getUniversity() const override {
        return studentUniversity;
    }

    std::string getType() const override {
        return "Student";
    }
};

class Teacher : virtual public Person {
protected:
    std::string teacherUniversity;
    std::string position;

public:
    Teacher(const std::string& name = "", const std::string& gen = "", int a = 0,
        const std::string& uni = "", const std::string& pos = "")
        : Person(name, gen, a), teacherUniversity(uni), position(pos) {
    }

    void input() override {
        Person::input();
        std::cout << "Enter university: ";
        std::getline(std::cin, teacherUniversity);
        std::cout << "Enter position: ";
        std::getline(std::cin, position);
    }

    void output() const override {
        Person::output();
        std::cout << "University: " << teacherUniversity << "\n";
        std::cout << "Position: " << position << "\n";
    }

    std::string getUniversity() const override {
        return teacherUniversity;
    }

    std::string getType() const override {
        return "Teacher";
    }
};

class Assistant : public Student, public Teacher {
private:
    std::string assistantUniversity;

public:
    Assistant(const std::string& name = "", const std::string& gen = "", int a = 0,
        int c = 1, const std::string& grp = "", const std::string& uni = "",
        const std::string& pos = "")
        : Person(name, gen, a), Student(name, gen, a, c, grp, uni), Teacher(name, gen, a, uni, pos), assistantUniversity(uni) {
    }

    void input() override {
        Person::input();
        std::cout << "Enter course: ";
        std::cin >> course;
        std::cin.ignore();
        std::cout << "Enter group: ";
        std::getline(std::cin, group);
        std::cout << "Enter university: ";
        std::getline(std::cin, assistantUniversity);
        std::cout << "Enter position: ";
        std::getline(std::cin, position);

        studentUniversity = assistantUniversity;
        teacherUniversity = assistantUniversity;
    }

    void output() const override {
        Person::output();
        std::cout << "Course: " << course << "\n";
        std::cout << "Group: " << group << "\n";
        std::cout << "University: " << assistantUniversity << "\n";
        std::cout << "Position: " << position << "\n";
    }

    std::string getUniversity() const override {
        return assistantUniversity;
    }

    std::string getType() const override {
        return "Assistant";
    }
};

void demonstrateRational() {
    try {
        std::cout << "~~~ Rational Numbers Demo ~~~\n";

        Rational r1, r2;

        std::cout << "Enter first rational number (format: numerator/denominator): ";
        std::cin >> r1;

        std::cout << "Enter second rational number (format: numerator/denominator): ";
        std::cin >> r2;

        std::cout << "r1 = " << r1 << "\n";
        std::cout << "r2 = " << r2 << "\n";
        std::cout << "r1 + r2 = " << r1 + r2 << "\n";
        std::cout << "r1 - r2 = " << r1 - r2 << "\n";
        std::cout << "r1 * r2 = " << r1 * r2 << "\n";
        std::cout << "r1 / r2 = " << r1 / r2 << "\n";
        std::cout << "-r1 = " << -r1 << "\n";

        std::cout << "Enter filename to save r1: ";
        std::string filename;
        std::cin >> filename;
        writeToFile(r1, filename);
        std::cout << "r1 saved to file: " << filename << "\n";

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

void demonstratePeople() {
    try {
        std::cout << "~~~ People Management Demo ~~~\n";

        int n;
        std::cout << "Enter number of people: ";
        std::cin >> n;
        std::cin.ignore();

        if (n <= 0) {
            throw std::invalid_argument("Number of people must be positive");
        }

        std::vector<std::unique_ptr<Person>> people;

        for (int i = 0; i < n; ++i) {
            std::cout << "\nPerson " << i + 1 << ":\n";
            std::cout << "Choose type (1 - Student, 2 - Teacher, 3 - Assistant): ";
            int type;
            std::cin >> type;
            std::cin.ignore();

            std::unique_ptr<Person> person;

            switch (type) {
            case 1:
                person = std::make_unique<Student>();
                break;
            case 2:
                person = std::make_unique<Teacher>();
                break;
            case 3:
                person = std::make_unique<Assistant>();
                break;
            default:
                throw std::invalid_argument("Invalid person type");
            }

            person->input();
            people.push_back(std::move(person));
        }

        std::cout << "\n~~~ All People ~~~\n";
        for (size_t i = 0; i < people.size(); ++i) {
            std::cout << "\nPerson " << i + 1 << " (" << people[i]->getType() << "):\n";
            people[i]->output();
            std::cout << "University: " << people[i]->getUniversity() << "\n";
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

int main() {
    int choice;

    do {
        std::cout << "\n~~~ MAIN MENU ~~~\n";
        std::cout << "1. Demonstrate Rational Numbers\n";
        std::cout << "2. Demonstrate People Management\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case 1:
            demonstrateRational();
            break;
        case 2:
            demonstratePeople();
            break;
        case 3:
            std::cout << "Bye!\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}