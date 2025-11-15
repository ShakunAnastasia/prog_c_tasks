#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <memory>
#include <map>
#include <set>
#include <functional>
#include <chrono>
#include <ctime>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef M_E
#define M_E 2.71828182845904523536
#endif

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

class Person {
protected:
    std::string firstName;
    std::string lastName;

public:
    Person(const std::string& first = "", const std::string& last = "")
        : firstName(first), lastName(last) {
    }

    virtual ~Person() = default;

    std::string getFirstName() const { return firstName; }
    std::string getLastName() const { return lastName; }
    void setFirstName(const std::string& first) { firstName = first; }
    void setLastName(const std::string& last) { lastName = last; }
};

class Passenger : public Person {
private:
    std::string departure;
    std::string destination;
    int seatNumber;

public:
    Passenger(const std::string& first = "", const std::string& last = "",
        const std::string& dep = "", const std::string& dest = "", int seat = 0)
        : Person(first, last), departure(dep), destination(dest), seatNumber(seat) {
    }

    std::string getDeparture() const { return departure; }
    std::string getDestination() const { return destination; }
    int getSeatNumber() const { return seatNumber; }
    void setDeparture(const std::string& dep) { departure = dep; }
    void setDestination(const std::string& dest) { destination = dest; }
    void setSeatNumber(int seat) { seatNumber = seat; }
};

class TicketOffice {
private:
    std::vector<Passenger> passengers;
    std::string filename = "passengers.dat";

    void saveToFile() {
        std::ofstream file(filename, std::ios::binary);
        if (!file) {
            throw std::runtime_error("Cannot open file for writing");
        }

        size_t count = passengers.size();
        file.write(reinterpret_cast<const char*>(&count), sizeof(count));

        for (const auto& passenger : passengers) {
            size_t len = passenger.getFirstName().length();
            file.write(reinterpret_cast<const char*>(&len), sizeof(len));
            file.write(passenger.getFirstName().c_str(), len);

            len = passenger.getLastName().length();
            file.write(reinterpret_cast<const char*>(&len), sizeof(len));
            file.write(passenger.getLastName().c_str(), len);

            len = passenger.getDeparture().length();
            file.write(reinterpret_cast<const char*>(&len), sizeof(len));
            file.write(passenger.getDeparture().c_str(), len);

            len = passenger.getDestination().length();
            file.write(reinterpret_cast<const char*>(&len), sizeof(len));
            file.write(passenger.getDestination().c_str(), len);

            int seat = passenger.getSeatNumber();
            file.write(reinterpret_cast<const char*>(&seat), sizeof(seat));
        }
    }

    void loadFromFile() {
        std::ifstream file(filename, std::ios::binary);
        if (!file) {
            return;
        }

        passengers.clear();
        size_t count;
        file.read(reinterpret_cast<char*>(&count), sizeof(count));

        for (size_t i = 0; i < count; ++i) {
            size_t len;
            std::string first, last, dep, dest;
            int seat;

            file.read(reinterpret_cast<char*>(&len), sizeof(len));
            first.resize(len);
            file.read(&first[0], len);

            file.read(reinterpret_cast<char*>(&len), sizeof(len));
            last.resize(len);
            file.read(&last[0], len);

            file.read(reinterpret_cast<char*>(&len), sizeof(len));
            dep.resize(len);
            file.read(&dep[0], len);

            file.read(reinterpret_cast<char*>(&len), sizeof(len));
            dest.resize(len);
            file.read(&dest[0], len);

            file.read(reinterpret_cast<char*>(&seat), sizeof(seat));

            passengers.emplace_back(first, last, dep, dest, seat);
        }
    }

public:
    TicketOffice() {
        loadFromFile();
    }

    ~TicketOffice() {
        try {
            saveToFile();
        }
        catch (...) {
        }
    }

    void addPassenger(const Passenger& passenger) {
        passengers.push_back(passenger);
        saveToFile();
    }

    void displayAllPassengers() const {
        if (passengers.empty()) {
            std::cout << "No passengers found.\n";
            return;
        }

        for (const auto& passenger : passengers) {
            std::cout << "Name: " << passenger.getFirstName() << " " << passenger.getLastName()
                << ", Departure: " << passenger.getDeparture()
                << ", Destination: " << passenger.getDestination()
                << ", Seat: " << passenger.getSeatNumber() << "\n";
        }
    }

    std::vector<Passenger> findByLastName(const std::string& lastName) const {
        std::vector<Passenger> result;
        for (const auto& passenger : passengers) {
            if (passenger.getLastName() == lastName) {
                result.push_back(passenger);
            }
        }
        return result;
    }

    std::vector<Passenger> findByDeparture(const std::string& departure) const {
        std::vector<Passenger> result;
        for (const auto& passenger : passengers) {
            if (passenger.getDeparture() == departure) {
                result.push_back(passenger);
            }
        }
        return result;
    }

    std::vector<Passenger> findByDestination(const std::string& destination) const {
        std::vector<Passenger> result;
        for (const auto& passenger : passengers) {
            if (passenger.getDestination() == destination) {
                result.push_back(passenger);
            }
        }
        return result;
    }

    std::vector<Passenger> findBySeat(int seat) const {
        std::vector<Passenger> result;
        for (const auto& passenger : passengers) {
            if (passenger.getSeatNumber() == seat) {
                result.push_back(passenger);
            }
        }
        return result;
    }

    int findEmptySeat(int maxSeats) const {
        std::set<int> occupiedSeats;
        for (const auto& passenger : passengers) {
            occupiedSeats.insert(passenger.getSeatNumber());
        }

        for (int seat = 1; seat <= maxSeats; ++seat) {
            if (occupiedSeats.find(seat) == occupiedSeats.end()) {
                return seat;
            }
        }
        return -1;
    }
};

class Student : public Person {
private:
    std::vector<int> grades5Scale;
    std::vector<int> grades100Scale;

public:
    Student(const std::string& first = "", const std::string& last = "")
        : Person(first, last) {
    }

    void addGrade5Scale(int grade) {
        if (grade >= 1 && grade <= 5) {
            grades5Scale.push_back(grade);
        }
    }

    void addGrade100Scale(int grade) {
        if (grade >= 0 && grade <= 100) {
            grades100Scale.push_back(grade);
        }
    }

    const std::vector<int>& getGrades5Scale() const { return grades5Scale; }
    const std::vector<int>& getGrades100Scale() const { return grades100Scale; }

    double getAverage5Scale() const {
        if (grades5Scale.empty()) return 0.0;
        double sum = 0.0;
        for (int grade : grades5Scale) {
            sum += grade;
        }
        return sum / grades5Scale.size();
    }

    double getAverage100Scale() const {
        if (grades100Scale.empty()) return 0.0;
        double sum = 0.0;
        for (int grade : grades100Scale) {
            sum += grade;
        }
        return sum / grades100Scale.size();
    }

    bool qualifiesForScholarshipOld() const {
        return getAverage5Scale() >= 4.0;
    }

    double getRating() const {
        return (getAverage5Scale() * 20 + getAverage100Scale()) / 2.0;
    }
};

class ScholarshipCalculator {
private:
    std::vector<Student> students;

public:
    void addStudent(const Student& student) {
        students.push_back(student);
    }

    std::vector<std::string> getOldScholarshipRecipients() const {
        std::vector<std::string> recipients;
        for (const auto& student : students) {
            if (student.qualifiesForScholarshipOld()) {
                recipients.push_back(student.getFirstName() + " " + student.getLastName());
            }
        }
        return recipients;
    }

    std::vector<std::string> getNewScholarshipRecipients() const {
        if (students.empty()) return {};

        std::vector<std::pair<double, std::string>> studentRatings;
        for (const auto& student : students) {
            studentRatings.emplace_back(student.getRating(),
                student.getFirstName() + " " + student.getLastName());
        }

        std::sort(studentRatings.begin(), studentRatings.end(),
            [](const auto& a, const auto& b) { return a.first > b.first; });

        size_t recipientsCount = students.size() * 0.4;
        if (recipientsCount == 0 && !students.empty()) {
            recipientsCount = 1;
        }

        std::vector<std::string> recipients;
        for (size_t i = 0; i < recipientsCount && i < studentRatings.size(); ++i) {
            recipients.push_back(studentRatings[i].second);
        }

        return recipients;
    }
};

class Word {
protected:
    std::string prefix;
    std::string prefix2;
    std::string root;
    std::string suffix;
    std::string ending;

public:
    Word(const std::string& pref = "", const std::string& pref2 = "",
        const std::string& rt = "", const std::string& suff = "", const std::string& end = "")
        : prefix(pref), prefix2(pref2), root(rt), suffix(suff), ending(end) {
    }

    virtual ~Word() = default;

    std::string getPrefix() const { return prefix; }
    std::string getPrefix2() const { return prefix2; }
    std::string getRoot() const { return root; }
    std::string getSuffix() const { return suffix; }
    std::string getEnding() const { return ending; }

    void setPrefix(const std::string& pref) { prefix = pref; }
    void setPrefix2(const std::string& pref2) { prefix2 = pref2; }
    void setRoot(const std::string& rt) { root = rt; }
    void setSuffix(const std::string& suff) { suffix = suff; }
    void setEnding(const std::string& end) { ending = end; }

    virtual std::string getFullWord() const {
        return prefix + prefix2 + root + suffix + ending;
    }

    virtual void changeGender(const std::string& gender) {}
    virtual void changeNumber(const std::string& number) {}
    virtual void changePerson(const std::string& person) {}
    virtual void changeCase(const std::string& wordCase) {}
};

class Noun : public Word {
private:
    std::string gender;
    std::string number;
    std::string wordCase;

public:
    Noun(const std::string& word = "") : Word("", "", word, "", ""), gender("masculine"), number("singular"), wordCase("nominative") {}

    void plural() {
        if (number == "singular") {
            if (ending.empty()) {
                ending = "s";
            }
            number = "plural";
        }
    }

    void changeCase(const std::string& newCase) override {
        wordCase = newCase;
        if (newCase == "genitive") {
            if (number == "singular") {
                ending = "'s";
            }
            else {
                ending = "s'";
            }
        }
        else if (newCase == "nominative") {
            if (number == "plural") {
                ending = "s";
            }
            else {
                ending = "";
            }
        }
    }

    void changeNumber(const std::string& num) override {
        number = num;
        if (num == "plural") {
            plural();
        }
    }

    std::string getFullWord() const override {
        return prefix + prefix2 + root + suffix + ending;
    }
};

class Verb : public Word {
private:
    std::string person;
    std::string number;
    std::string tense;

public:
    Verb(const std::string& word = "") : Word("", "", word, "", ""), person("first"), number("singular"), tense("present") {}

    void third() {
        if (person != "third") {
            person = "third";
            if (number == "singular") {
                if (!root.empty() && (root.back() == 'o' || root.back() == 's' || root.back() == 'x' ||
                    root.back() == 'z' || root.substr(root.length() - 2) == "sh" ||
                    root.substr(root.length() - 2) == "ch")) {
                    ending = "es";
                }
                else if (!root.empty() && root.back() == 'y') {
                    root.pop_back();
                    ending = "ies";
                }
                else {
                    ending = "s";
                }
            }
        }
    }

    void plural() {
        number = "plural";
        ending = "";
        person = "first";
    }

    void changePerson(const std::string& newPerson) override {
        person = newPerson;
        if (newPerson == "third" && number == "singular") {
            third();
        }
        else {
            ending = "";
        }
    }

    void changeNumber(const std::string& num) override {
        number = num;
        if (num == "plural") {
            plural();
        }
        else if (num == "singular" && person == "third") {
            third();
        }
    }

    std::string getFullWord() const override {
        return prefix + prefix2 + root + suffix + ending;
    }
};

class Adjective : public Word {
private:
    std::string degree;
    std::string number;

public:
    Adjective(const std::string& word = "") : Word("", "", word, "", ""), degree("positive"), number("singular") {}

    void comparative() {
        degree = "comparative";
        if (root.length() > 2) {
            if (root.back() == 'y') {
                root.pop_back();
                ending = "ier";
            }
            else {
                ending = "er";
            }
        }
    }

    void superlative() {
        degree = "superlative";
        if (root.length() > 2) {
            if (root.back() == 'y') {
                root.pop_back();
                ending = "iest";
            }
            else {
                ending = "est";
            }
        }
    }

    void changeNumber(const std::string& num) override {
        number = num;
    }

    std::string getFullWord() const override {
        return prefix + prefix2 + root + suffix + ending;
    }
};

class Shape {
public:
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual double getPerimeter() const = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void rotate(double angle) = 0;
};

class Point {
public:
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

class Rectangle : public Shape {
private:
    Point topLeft;
    double width, height;

public:
    Rectangle(const Point& tl = Point(), double w = 0, double h = 0) : topLeft(tl), width(w), height(h) {}

    double getWidth() const { return width; }
    double getHeight() const { return height; }

    double getArea() const override {
        return width * height;
    }

    double getPerimeter() const override {
        return 2 * (width + height);
    }

    Point getCenter() const {
        return Point(topLeft.x + width / 2, topLeft.y - height / 2);
    }

    void move(double dx, double dy) override {
        topLeft.x += dx;
        topLeft.y += dy;
    }

    void rotate(double angle) override {
        Point center = getCenter();
        double s = sin(angle);
        double c = cos(angle);

        topLeft.x -= center.x;
        topLeft.y -= center.y;

        double xnew = topLeft.x * c - topLeft.y * s;
        double ynew = topLeft.x * s + topLeft.y * c;

        topLeft.x = xnew + center.x;
        topLeft.y = ynew + center.y;
    }

    bool intersects(const Rectangle& other) const {
        return !(topLeft.x + width < other.topLeft.x ||
            other.topLeft.x + other.width < topLeft.x ||
            topLeft.y - height > other.topLeft.y ||
            other.topLeft.y - other.height > topLeft.y);
    }
};

class Triangle : public Shape {
private:
    Point bottomLeft;
    double base;
    double angle1, angle2;

public:
    Triangle(const Point& bl = Point(), double b = 0, double a1 = 0, double a2 = 0)
        : bottomLeft(bl), base(b), angle1(a1), angle2(a2) {
    }

    double getSide1() const {
        return base * sin(angle2 * M_PI / 180) / sin((180 - angle1 - angle2) * M_PI / 180);
    }

    double getSide2() const {
        return base * sin(angle1 * M_PI / 180) / sin((180 - angle1 - angle2) * M_PI / 180);
    }

    double getArea() const override {
        double side1 = getSide1();
        double side2 = getSide2();
        double s = (base + side1 + side2) / 2;
        return sqrt(s * (s - base) * (s - side1) * (s - side2));
    }

    double getPerimeter() const override {
        return base + getSide1() + getSide2();
    }

    Point getCenter() const {
        double side1 = getSide1();
        double side2 = getSide2();
        double x = (bottomLeft.x * side2 + (bottomLeft.x + base) * side1 + bottomLeft.x * base) / (base + side1 + side2);
        double y = (bottomLeft.y * side2 + bottomLeft.y * side1 + (bottomLeft.y + side1 * sin(angle1 * M_PI / 180)) * base) / (base + side1 + side2);
        return Point(x, y);
    }

    void move(double dx, double dy) override {
        bottomLeft.x += dx;
        bottomLeft.y += dy;
    }

    void rotate(double angle) override {
    }
};

class Ellipse : public Shape {
private:
    Point focus1, focus2;
    double radius1, radius2;

public:
    Ellipse(const Point& f1 = Point(), const Point& f2 = Point(), double r1 = 0, double r2 = 0)
        : focus1(f1), focus2(f2), radius1(r1), radius2(r2) {
    }

    double getMajorRadius() const { return std::max(radius1, radius2); }
    double getMinorRadius() const { return std::min(radius1, radius2); }

    double getArea() const override {
        return M_PI * radius1 * radius2;
    }

    double getPerimeter() const override {
        double a = getMajorRadius();
        double b = getMinorRadius();
        return M_PI * (3 * (a + b) - sqrt((3 * a + b) * (a + 3 * b)));
    }

    Point getCenter() const {
        return Point((focus1.x + focus2.x) / 2, (focus1.y + focus2.y) / 2);
    }

    void move(double dx, double dy) override {
        focus1.x += dx;
        focus1.y += dy;
        focus2.x += dx;
        focus2.y += dy;
    }

    void rotate(double angle) override {
        Point center = getCenter();
        double s = sin(angle);
        double c = cos(angle);

        focus1.x -= center.x;
        focus1.y -= center.y;
        focus2.x -= center.x;
        focus2.y -= center.y;

        double x1new = focus1.x * c - focus1.y * s;
        double y1new = focus1.x * s + focus1.y * c;
        double x2new = focus2.x * c - focus2.y * s;
        double y2new = focus2.x * s + focus2.y * c;

        focus1.x = x1new + center.x;
        focus1.y = y1new + center.y;
        focus2.x = x2new + center.x;
        focus2.y = y2new + center.y;
    }
};

class Shape2D {
public:
    virtual ~Shape2D() = default;
    virtual double getArea() const = 0;
    virtual double getPerimeter() const = 0;
    virtual void move(double dx, double dy) = 0;
};

class Trapezoid : public Shape2D {
private:
    Point topLeft;
    double topBase, bottomBase, height;

public:
    Trapezoid(const Point& tl = Point(), double tb = 0, double bb = 0, double h = 0)
        : topLeft(tl), topBase(tb), bottomBase(bb), height(h) {
    }

    double getArea() const override {
        return (topBase + bottomBase) * height / 2;
    }

    double getPerimeter() const override {
        double side = sqrt(height * height + pow((bottomBase - topBase) / 2, 2));
        return topBase + bottomBase + 2 * side;
    }

    void move(double dx, double dy) override {
        topLeft.x += dx;
        topLeft.y += dy;
    }

    void rotate(double angle) {
    }
};

class Parallelogram : public Shape2D {
private:
    Point topLeft;
    double base, height, angle;

public:
    Parallelogram(const Point& tl = Point(), double b = 0, double h = 0, double a = 0)
        : topLeft(tl), base(b), height(h), angle(a) {
    }

    double getArea() const override {
        return base * height;
    }

    double getPerimeter() const override {
        double side = height / sin(angle * M_PI / 180);
        return 2 * (base + side);
    }

    void move(double dx, double dy) override {
        topLeft.x += dx;
        topLeft.y += dy;
    }

    void rotate(double rotAngle) {
        angle += rotAngle;
    }
};

class Circle : public Shape2D {
private:
    Point center;
    double radius;

public:
    Circle(const Point& c = Point(), double r = 0) : center(c), radius(r) {}

    double getArea() const override {
        return M_PI * radius * radius;
    }

    double getPerimeter() const override {
        return 2 * M_PI * radius;
    }

    void move(double dx, double dy) override {
        center.x += dx;
        center.y += dy;
    }

    void rotate(double angle) {
    }
};

class Shape3D {
public:
    virtual ~Shape3D() = default;
    virtual double getVolume() const = 0;
    virtual double getSurfaceArea() const = 0;
    virtual int getVertexCount() const = 0;
};

class Parallelepiped : public Shape3D {
private:
    double length, width, height;

public:
    Parallelepiped(double l = 0, double w = 0, double h = 0) : length(l), width(w), height(h) {}

    double getVolume() const override {
        return length * width * height;
    }

    double getSurfaceArea() const override {
        return 2 * (length * width + length * height + width * height);
    }

    int getVertexCount() const override {
        return 8;
    }
};

class Pyramid3 : public Shape3D {
private:
    double baseSide, height;

public:
    Pyramid3(double side = 0, double h = 0) : baseSide(side), height(h) {}

    double getVolume() const override {
        double baseArea = (sqrt(3) / 4) * baseSide * baseSide;
        return (baseArea * height) / 3;
    }

    double getSurfaceArea() const override {
        double baseArea = (sqrt(3) / 4) * baseSide * baseSide;
        double slantHeight = sqrt(height * height + pow(baseSide / (2 * sqrt(3)), 2));
        double triangleArea = (baseSide * slantHeight) / 2;
        return baseArea + 3 * triangleArea;
    }

    int getVertexCount() const override {
        return 4;
    }
};

class Pyramid4 : public Shape3D {
private:
    double baseLength, baseWidth, height;

public:
    Pyramid4(double length = 0, double width = 0, double h = 0) : baseLength(length), baseWidth(width), height(h) {}

    double getVolume() const override {
        return (baseLength * baseWidth * height) / 3;
    }

    double getSurfaceArea() const override {
        double baseArea = baseLength * baseWidth;
        double slant1 = sqrt(height * height + pow(baseLength / 2, 2));
        double slant2 = sqrt(height * height + pow(baseWidth / 2, 2));
        double triangleArea1 = (baseLength * slant2) / 2;
        double triangleArea2 = (baseWidth * slant1) / 2;
        return baseArea + 2 * triangleArea1 + 2 * triangleArea2;
    }

    int getVertexCount() const override {
        return 5;
    }
};

class Equation {
protected:
    double a, b;

public:
    Equation(double a = 0, double b = 0) : a(a), b(b) {}
    virtual ~Equation() = default;

    virtual std::vector<double> solve() const {
        std::vector<double> solutions;
        if (a == 0) {
            if (b == 0) {
            }
            else {
            }
        }
        else {
            solutions.push_back(-b / a);
        }
        return solutions;
    }

    virtual bool hasInfiniteSolutions() const {
        return a == 0 && b == 0;
    }

    virtual void setCoefficients(double a_val, double b_val) {
        a = a_val;
        b = b_val;
    }

    virtual void input() {
        std::cout << "Enter coefficient a: ";
        std::cin >> a;
        std::cout << "Enter coefficient b: ";
        std::cin >> b;
    }

    virtual void display() const {
        std::cout << a << "x + " << b << " = 0";
    }
};

class QuadraticEquation : public Equation {
protected:
    double c;

public:
    QuadraticEquation(double a = 0, double b = 0, double c = 0) : Equation(a, b), c(c) {}

    std::vector<double> solve() const override {
        std::vector<double> solutions;

        if (a == 0) {
            return Equation::solve();
        }

        double discriminant = b * b - 4 * a * c;

        if (discriminant > 0) {
            solutions.push_back((-b + sqrt(discriminant)) / (2 * a));
            solutions.push_back((-b - sqrt(discriminant)) / (2 * a));
        }
        else if (discriminant == 0) {
            solutions.push_back(-b / (2 * a));
        }

        return solutions;
    }

    bool hasInfiniteSolutions() const override {
        return a == 0 && b == 0 && c == 0;
    }

    void setCoefficients(double a_val, double b_val, double c_val) {
        a = a_val;
        b = b_val;
        c = c_val;
    }

    void input() override {
        Equation::input();
        std::cout << "Enter coefficient c: ";
        std::cin >> c;
    }

    void display() const override {
        std::cout << a << "x² + " << b << "x + " << c << " = 0";
    }
};

class BiquadraticEquation : public QuadraticEquation {
public:
    BiquadraticEquation(double a = 0, double b = 0, double c = 0) : QuadraticEquation(a, b, c) {}

    std::vector<double> solve() const override {
        std::vector<double> solutions;

        if (a == 0 && b == 0 && c == 0) {
            return solutions;
        }

        QuadraticEquation quad(a, b, c);
        auto tempSolutions = quad.solve();

        for (double sol : tempSolutions) {
            if (sol >= 0) {
                solutions.push_back(sqrt(sol));
                solutions.push_back(-sqrt(sol));
            }
        }

        return solutions;
    }

    void input() override {
        std::cout << "Enter coefficient a (for x⁴): ";
        std::cin >> a;
        std::cout << "Enter coefficient b (for x²): ";
        std::cin >> b;
        std::cout << "Enter coefficient c: ";
        std::cin >> c;
    }

    void display() const override {
        std::cout << a << "x⁴ + " << b << "x² + " << c << " = 0";
    }
};

class Car {
protected:
    double distanceTraveled;
    double fuelRemaining;

public:
    Car(double fuel = 0) : distanceTraveled(0), fuelRemaining(fuel) {}
    virtual ~Car() = default;

    virtual double fuelPerKm() const = 0;

    bool go(double distance) {
        double fuelNeeded = distance * fuelPerKm();
        if (fuelNeeded <= fuelRemaining) {
            distanceTraveled += distance;
            fuelRemaining -= fuelNeeded;
            return true;
        }
        return false;
    }

    double getDistanceTraveled() const { return distanceTraveled; }
    double getFuelRemaining() const { return fuelRemaining; }
    void refuel(double amount) { fuelRemaining += amount; }
};

class Personal : public Car {
private:
    int passengers;

public:
    Personal(double fuel = 0, int pass = 0) : Car(fuel), passengers(pass) {}

    double fuelPerKm() const override {
        double baseConsumption = 0.08;
        return baseConsumption * (1 + passengers * 0.1);
    }

    void setPassengers(int pass) { passengers = pass; }
};

class Truck : public Car {
private:
    double cargoWeight;

public:
    Truck(double fuel = 0, double weight = 0) : Car(fuel), cargoWeight(weight) {}

    double fuelPerKm() const override {
        double baseConsumption = 0.25;
        return baseConsumption * (1 + cargoWeight * 0.25);
    }

    void setCargoWeight(double weight) { cargoWeight = weight; }
};

class EquationRoot {
protected:
    double leftBound, rightBound;

public:
    EquationRoot(double left = -10, double right = 10) : leftBound(left), rightBound(right) {}
    virtual ~EquationRoot() = default;

    virtual double function(double x) const = 0;
    virtual void display() const = 0;
    virtual void inputParameters() = 0;

    double findRoot(double epsilon = 1e-6, int maxIterations = 1000) const {
        double a = leftBound;
        double b = rightBound;

        if (function(a) * function(b) > 0) {
            throw std::runtime_error("No root in the given interval");
        }

        for (int i = 0; i < maxIterations; ++i) {
            double c = (a + b) / 2;
            double fc = function(c);

            if (fabs(fc) < epsilon || (b - a) / 2 < epsilon) {
                return c;
            }

            if (function(a) * fc < 0) {
                b = c;
            }
            else {
                a = c;
            }
        }

        throw std::runtime_error("Maximum iterations reached");
    }

    void setInterval(double left, double right) {
        leftBound = left;
        rightBound = right;
    }
};

class LinearEquation : public EquationRoot {
private:
    double a, b;

public:
    LinearEquation(double a_val = 1, double b_val = 0) : EquationRoot(), a(a_val), b(b_val) {}

    double function(double x) const override {
        return a * x + b;
    }

    void display() const override {
        std::cout << a << "x + " << b << " = 0";
    }

    void inputParameters() override {
        std::cout << "Enter coefficient a: ";
        std::cin >> a;
        std::cout << "Enter coefficient b: ";
        std::cin >> b;
    }
};

class CubicEquation : public EquationRoot {
private:
    double a, b, c, d;

public:
    CubicEquation(double a_val = 1, double b_val = 0, double c_val = 0, double d_val = 0)
        : EquationRoot(), a(a_val), b(b_val), c(c_val), d(d_val) {
    }

    double function(double x) const override {
        return a * x * x * x + b * x * x + c * x + d;
    }

    void display() const override {
        std::cout << a << "x³ + " << b << "x² + " << c << "x + " << d << " = 0";
    }

    void inputParameters() override {
        std::cout << "Enter coefficient a: ";
        std::cin >> a;
        std::cout << "Enter coefficient b: ";
        std::cin >> b;
        std::cout << "Enter coefficient c: ";
        std::cin >> c;
        std::cout << "Enter coefficient d: ";
        std::cin >> d;
    }
};

class SineEquation : public EquationRoot {
private:
    double amplitude, frequency, phase;

public:
    SineEquation(double amp = 1, double freq = 1, double ph = 0)
        : EquationRoot(), amplitude(amp), frequency(freq), phase(ph) {
    }

    double function(double x) const override {
        return amplitude * sin(frequency * x + phase);
    }

    void display() const override {
        std::cout << amplitude << " * sin(" << frequency << "x + " << phase << ") = 0";
    }

    void inputParameters() override {
        std::cout << "Enter amplitude: ";
        std::cin >> amplitude;
        std::cout << "Enter frequency: ";
        std::cin >> frequency;
        std::cout << "Enter phase: ";
        std::cin >> phase;
    }
};

class ExponentialEquation : public EquationRoot {
private:
    double base, coefficient;

public:
    ExponentialEquation(double b = M_E, double coeff = 1)
        : EquationRoot(), base(b), coefficient(coeff) {
    }

    double function(double x) const override {
        return coefficient * pow(base, x);
    }

    void display() const override {
        std::cout << coefficient << " * " << base << "^x = 0";
    }

    void inputParameters() override {
        std::cout << "Enter base: ";
        std::cin >> base;
        std::cout << "Enter coefficient: ";
        std::cin >> coefficient;
    }
};

class Product {
protected:
    std::string name;
    std::string article;
    std::string unit;
    double price;
    std::string supplyDate;

public:
    Product(const std::string& n = "", const std::string& art = "", const std::string& u = "",
        double p = 0, const std::string& date = "")
        : name(n), article(art), unit(u), price(p), supplyDate(date) {
    }

    virtual ~Product() = default;

    std::string getName() const { return name; }
    std::string getArticle() const { return article; }
    std::string getUnit() const { return unit; }
    double getPrice() const { return price; }
    std::string getSupplyDate() const { return supplyDate; }

    void setPrice(double p) { price = p; }

    virtual void display() const {
        std::cout << "Name: " << name << ", Article: " << article
            << ", Unit: " << unit << ", Price: " << price
            << ", Supply Date: " << supplyDate;
    }

    virtual std::string getType() const = 0;
};

class Toy : public Product {
private:
    int ageLimit;

public:
    Toy(const std::string& n = "", const std::string& art = "", const std::string& u = "",
        double p = 0, const std::string& date = "", int age = 0)
        : Product(n, art, u, p, date), ageLimit(age) {
    }

    void display() const override {
        Product::display();
        std::cout << ", Age Limit: " << ageLimit << "+";
    }

    std::string getType() const override { return "Toy"; }
    int getAgeLimit() const { return ageLimit; }
};

class Food : public Product {
private:
    int expiryDays;

public:
    Food(const std::string& n = "", const std::string& art = "", const std::string& u = "",
        double p = 0, const std::string& date = "", int expiry = 0)
        : Product(n, art, u, p, date), expiryDays(expiry) {
    }

    void display() const override {
        Product::display();
        std::cout << ", Expiry Days: " << expiryDays;
    }

    std::string getType() const override { return "Food"; }
    int getExpiryDays() const { return expiryDays; }
};

class Appliance : public Product {
private:
    bool hasWarranty;
    int warrantyMonths;

public:
    Appliance(const std::string& n = "", const std::string& art = "", const std::string& u = "",
        double p = 0, const std::string& date = "", bool warranty = false, int months = 0)
        : Product(n, art, u, p, date), hasWarranty(warranty), warrantyMonths(months) {
    }

    void display() const override {
        Product::display();
        std::cout << ", Warranty: " << (hasWarranty ? "Yes" : "No")
            << ", Warranty Months: " << warrantyMonths;
    }

    std::string getType() const override { return "Appliance"; }
    bool getHasWarranty() const { return hasWarranty; }
    int getWarrantyMonths() const { return warrantyMonths; }
};

class Store {
private:
    std::vector<std::shared_ptr<Product>> products;
    std::string filename = "products.dat";

public:
    void addProduct(std::shared_ptr<Product> product) {
        products.push_back(product);
    }

    std::vector<std::shared_ptr<Product>> findByName(const std::string& name) const {
        std::vector<std::shared_ptr<Product>> result;
        for (const auto& product : products) {
            if (product->getName() == name) {
                result.push_back(product);
            }
        }
        return result;
    }

    std::vector<std::shared_ptr<Product>> findByType(const std::string& type) const {
        std::vector<std::shared_ptr<Product>> result;
        for (const auto& product : products) {
            if (product->getType() == type) {
                result.push_back(product);
            }
        }
        return result;
    }

    void applyDiscounts() {
        auto now = std::chrono::system_clock::now();

        for (auto& product : products) {
            if (auto food = std::dynamic_pointer_cast<Food>(product)) {
                if (food->getExpiryDays() < 5) {
                    food->setPrice(food->getPrice() * 0.8);
                }
            }
            else if (auto appliance = std::dynamic_pointer_cast<Appliance>(product)) {
                if (appliance->getHasWarranty() && appliance->getWarrantyMonths() < 1) {
                    appliance->setPrice(appliance->getPrice() * 0.8);
                }
            }
        }
    }

    void displayAllProducts() const {
        if (products.empty()) {
            std::cout << "No products found.\n";
            return;
        }
        for (const auto& product : products) {
            product->display();
            std::cout << "\n";
        }
    }
};

class Address {
protected:
    std::string city;
    std::string street;
    int houseNumber;
    int apartmentNumber;

public:
    Address(const std::string& c = "", const std::string& s = "", int house = 0, int apartment = 0)
        : city(c), street(s), houseNumber(house), apartmentNumber(apartment) {
    }

    virtual ~Address() = default;

    std::string getCity() const { return city; }
    std::string getStreet() const { return street; }
    int getHouseNumber() const { return houseNumber; }
    int getApartmentNumber() const { return apartmentNumber; }

    virtual void display() const {
        std::cout << city << ", " << street << " " << houseNumber;
        if (apartmentNumber > 0) {
            std::cout << "/" << apartmentNumber;
        }
    }
};

class InternationalAddress : public Address {
private:
    std::string country;
    std::string postalCode;

public:
    InternationalAddress(const std::string& c = "", const std::string& s = "", int house = 0, int apartment = 0,
        const std::string& cntry = "", const std::string& code = "")
        : Address(c, s, house, apartment), country(cntry), postalCode(code) {
    }

    void display() const override {
        std::cout << country << ", " << city << ", " << street << " " << houseNumber;
        if (apartmentNumber > 0) {
            std::cout << "/" << apartmentNumber;
        }
        std::cout << ", " << postalCode;
    }

    std::string getCountry() const { return country; }
    std::string getPostalCode() const { return postalCode; }
};

class PersonWithAddress : public Person {
private:
    std::shared_ptr<Address> address;

public:
    PersonWithAddress(const std::string& first = "", const std::string& last = "",
        std::shared_ptr<Address> addr = nullptr)
        : Person(first, last), address(addr) {
    }

    void setAddress(std::shared_ptr<Address> addr) { address = addr; }
    std::shared_ptr<Address> getAddress() const { return address; }

    void display() const {
        std::cout << getFirstName() << " " << getLastName();
        if (address) {
            std::cout << " - ";
            address->display();
        }
        std::cout << "\n";
    }
};

class EAddress {
private:
    std::string email;
    std::string website;
    std::string phone;

public:
    EAddress(const std::string& e = "", const std::string& w = "", const std::string& p = "")
        : email(e), website(w), phone(p) {
    }

    std::string getEmail() const { return email; }
    std::string getWebsite() const { return website; }
    std::string getPhone() const { return phone; }

    std::string getEmailDomain() const {
        size_t pos = email.find('@');
        if (pos != std::string::npos) {
            return email.substr(pos + 1);
        }
        return "";
    }

    void display() const {
        std::cout << "Email: " << email << ", Phone: " << phone;
        if (!website.empty()) {
            std::cout << ", Website: " << website;
        }
    }
};

class PersonWithEAddress : public PersonWithAddress {
private:
    EAddress eAddress;

public:
    PersonWithEAddress(const std::string& first = "", const std::string& last = "",
        std::shared_ptr<Address> addr = nullptr, const EAddress& eAddr = EAddress())
        : PersonWithAddress(first, last, addr), eAddress(eAddr) {
    }

    void setEAddress(const EAddress& eAddr) { eAddress = eAddr; }
    EAddress getEAddress() const { return eAddress; }

    void displayFull() const {
        display();
        std::cout << " - ";
        eAddress.display();
        std::cout << "\n";
    }
};

class Number {
public:
    virtual ~Number() = default;
    virtual void input() = 0;
    virtual void display() const = 0;
    virtual std::shared_ptr<Number> add(const std::shared_ptr<Number>& other) const = 0;
    virtual std::shared_ptr<Number> multiply(const std::shared_ptr<Number>& other) const = 0;
    virtual std::shared_ptr<Number> divide(const std::shared_ptr<Number>& other) const = 0;
    virtual double toDouble() const = 0;
};

class RationalNumber : public Number {
private:
    int numerator, denominator;

public:
    RationalNumber(int num = 0, int den = 1) : numerator(num), denominator(den) {
        if (denominator == 0) throw std::runtime_error("Denominator cannot be zero");
        simplify();
    }

    void simplify() {
        int g = gcd(std::abs(numerator), std::abs(denominator));
        numerator /= g;
        denominator /= g;
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

    void input() override {
        std::cout << "Enter numerator: ";
        std::cin >> numerator;
        std::cout << "Enter denominator: ";
        std::cin >> denominator;
        if (denominator == 0) throw std::runtime_error("Denominator cannot be zero");
        simplify();
    }

    void display() const override {
        std::cout << numerator;
        if (denominator != 1) {
            std::cout << "/" << denominator;
        }
    }

    std::shared_ptr<Number> add(const std::shared_ptr<Number>& other) const override {
        auto rational = std::dynamic_pointer_cast<RationalNumber>(other);
        if (!rational) throw std::runtime_error("Type mismatch");

        int newNum = numerator * rational->denominator + rational->numerator * denominator;
        int newDen = denominator * rational->denominator;
        return std::make_shared<RationalNumber>(newNum, newDen);
    }

    std::shared_ptr<Number> multiply(const std::shared_ptr<Number>& other) const override {
        auto rational = std::dynamic_pointer_cast<RationalNumber>(other);
        if (!rational) throw std::runtime_error("Type mismatch");

        return std::make_shared<RationalNumber>(numerator * rational->numerator,
            denominator * rational->denominator);
    }

    std::shared_ptr<Number> divide(const std::shared_ptr<Number>& other) const override {
        auto rational = std::dynamic_pointer_cast<RationalNumber>(other);
        if (!rational) throw std::runtime_error("Type mismatch");

        return std::make_shared<RationalNumber>(numerator * rational->denominator,
            denominator * rational->numerator);
    }

    double toDouble() const override {
        return static_cast<double>(numerator) / denominator;
    }
};

class ComplexNumber : public Number {
private:
    double real, imaginary;

public:
    ComplexNumber(double r = 0, double i = 0) : real(r), imaginary(i) {}

    void input() override {
        std::cout << "Enter real part: ";
        std::cin >> real;
        std::cout << "Enter imaginary part: ";
        std::cin >> imaginary;
    }

    void display() const override {
        std::cout << real;
        if (imaginary >= 0) {
            std::cout << " + " << imaginary << "i";
        }
        else {
            std::cout << " - " << -imaginary << "i";
        }
    }

    std::shared_ptr<Number> add(const std::shared_ptr<Number>& other) const override {
        auto complex = std::dynamic_pointer_cast<ComplexNumber>(other);
        if (!complex) throw std::runtime_error("Type mismatch");

        return std::make_shared<ComplexNumber>(real + complex->real,
            imaginary + complex->imaginary);
    }

    std::shared_ptr<Number> multiply(const std::shared_ptr<Number>& other) const override {
        auto complex = std::dynamic_pointer_cast<ComplexNumber>(other);
        if (!complex) throw std::runtime_error("Type mismatch");

        double newReal = real * complex->real - imaginary * complex->imaginary;
        double newImag = real * complex->imaginary + imaginary * complex->real;
        return std::make_shared<ComplexNumber>(newReal, newImag);
    }

    std::shared_ptr<Number> divide(const std::shared_ptr<Number>& other) const override {
        auto complex = std::dynamic_pointer_cast<ComplexNumber>(other);
        if (!complex) throw std::runtime_error("Type mismatch");

        double denominator = complex->real * complex->real + complex->imaginary * complex->imaginary;
        double newReal = (real * complex->real + imaginary * complex->imaginary) / denominator;
        double newImag = (imaginary * complex->real - real * complex->imaginary) / denominator;
        return std::make_shared<ComplexNumber>(newReal, newImag);
    }

    double toDouble() const override {
        return real;
    }
};

class Polynomial {
private:
    std::vector<std::shared_ptr<Number>> coefficients;

public:
    void input() {
        int degree;
        std::cout << "Enter polynomial degree: ";
        std::cin >> degree;

        coefficients.resize(degree + 1);

        std::cout << "Choose number type (1 - Rational, 2 - Complex): ";
        int type;
        std::cin >> type;

        for (int i = degree; i >= 0; --i) {
            std::cout << "Coefficient for x^" << i << ": ";
            if (type == 1) {
                coefficients[i] = std::make_shared<RationalNumber>();
            }
            else {
                coefficients[i] = std::make_shared<ComplexNumber>();
            }
            coefficients[i]->input();
        }
    }

    std::shared_ptr<Number> evaluate(const std::shared_ptr<Number>& x) const {
        if (coefficients.empty()) {
            throw std::runtime_error("Polynomial is empty");
        }

        auto result = coefficients[0];
        auto x_power = std::make_shared<RationalNumber>(1, 1);

        for (size_t i = 1; i < coefficients.size(); ++i) {
            x_power = std::shared_ptr<RationalNumber>(dynamic_cast<RationalNumber*>(x_power->multiply(x).get()));
            auto term = coefficients[i]->multiply(x_power);
            result = result->add(term);
        }

        return result;
    }

    void display() const {
        bool first = true;
        for (int i = coefficients.size() - 1; i >= 0; --i) {
            if (!first) {
                std::cout << " + ";
            }
            coefficients[i]->display();
            if (i > 0) {
                std::cout << "x";
                if (i > 1) {
                    std::cout << "^" << i;
                }
            }
            first = false;
        }
        std::cout << "\n";
    }
};

class TaskManager {
private:
    void clearInputBuffer() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    int getValidatedInteger(const std::string& prompt) {
        int value;
        while (true) {
            std::cout << prompt;
            if (std::cin >> value) {
                clearInputBuffer();
                return value;
            }
            std::cout << "Invalid input. Please enter an integer.\n";
            clearInputBuffer();
        }
    }

    double getValidatedDouble(const std::string& prompt) {
        double value;
        while (true) {
            std::cout << prompt;
            if (std::cin >> value) {
                clearInputBuffer();
                return value;
            }
            std::cout << "Invalid input. Please enter a number.\n";
            clearInputBuffer();
        }
    }

    std::string getStringInput(const std::string& prompt) {
        std::string value;
        std::cout << prompt;
        std::getline(std::cin, value);
        return value;
    }

public:
    void task3() {
        std::cout << "\n~~~ Task 3: Ticket Office System.\n";

        TicketOffice office;

        while (true) {
            std::cout << "\nTicket Office Menu:\n";
            std::cout << "1. Add Passenger\n";
            std::cout << "2. Display All Passengers\n";
            std::cout << "3. Find by Last Name\n";
            std::cout << "4. Find by Departure\n";
            std::cout << "5. Find by Destination\n";
            std::cout << "6. Find by Seat\n";
            std::cout << "7. Find Empty Seat\n";
            std::cout << "8. Return to Main Menu\n";

            int choice = getValidatedInteger("Select option: ");

            switch (choice) {
            case 1: {
                std::string first = getStringInput("First Name: ");
                std::string last = getStringInput("Last Name: ");
                std::string dep = getStringInput("Departure: ");
                std::string dest = getStringInput("Destination: ");
                int seat = getValidatedInteger("Seat Number: ");

                office.addPassenger(Passenger(first, last, dep, dest, seat));
                std::cout << "Passenger added successfully.\n";
                break;
            }
            case 2:
                office.displayAllPassengers();
                break;
            case 3: {
                std::string lastName = getStringInput("Enter last name: ");
                auto results = office.findByLastName(lastName);
                for (const auto& p : results) {
                    std::cout << p.getFirstName() << " " << p.getLastName()
                        << " - " << p.getDeparture() << " to " << p.getDestination()
                        << ", Seat: " << p.getSeatNumber() << "\n";
                }
                break;
            }
            case 4: {
                std::string departure = getStringInput("Enter departure: ");
                auto results = office.findByDeparture(departure);
                for (const auto& p : results) {
                    std::cout << p.getFirstName() << " " << p.getLastName()
                        << " - " << p.getDeparture() << " to " << p.getDestination()
                        << ", Seat: " << p.getSeatNumber() << "\n";
                }
                break;
            }
            case 5: {
                std::string destination = getStringInput("Enter destination: ");
                auto results = office.findByDestination(destination);
                for (const auto& p : results) {
                    std::cout << p.getFirstName() << " " << p.getLastName()
                        << " - " << p.getDeparture() << " to " << p.getDestination()
                        << ", Seat: " << p.getSeatNumber() << "\n";
                }
                break;
            }
            case 6: {
                int seat = getValidatedInteger("Enter seat number: ");
                auto results = office.findBySeat(seat);
                for (const auto& p : results) {
                    std::cout << p.getFirstName() << " " << p.getLastName()
                        << " - " << p.getDeparture() << " to " << p.getDestination()
                        << ", Seat: " << p.getSeatNumber() << "\n";
                }
                break;
            }
            case 7: {
                int maxSeats = getValidatedInteger("Enter maximum number of seats: ");
                int emptySeat = office.findEmptySeat(maxSeats);
                if (emptySeat != -1) {
                    std::cout << "First empty seat: " << emptySeat << "\n";
                }
                else {
                    std::cout << "No empty seats found.\n";
                }
                break;
            }
            case 8:
                return;
            default:
                std::cout << "Invalid choice.\n";
            }
        }
    }

    void task4() {
        std::cout << "\n~~~ TASK 4: Student Scholarship System.\n";

        ScholarshipCalculator calculator;

        while (true) {
            std::cout << "\nScholarship System Menu:\n";
            std::cout << "1. Add Student\n";
            std::cout << "2. Add Grades to Student\n";
            std::cout << "3. Calculate Old Scholarship\n";
            std::cout << "4. Calculate New Scholarship\n";
            std::cout << "5. Return to Main Menu\n";

            int choice = getValidatedInteger("Select option: ");

            switch (choice) {
            case 1: {
                std::string first = getStringInput("First Name: ");
                std::string last = getStringInput("Last Name: ");
                calculator.addStudent(Student(first, last));
                std::cout << "Student added successfully.\n";
                break;
            }
            case 2: {
                break;
            }
            case 3: {
                auto recipients = calculator.getOldScholarshipRecipients();
                std::cout << "Old Scholarship Recipients:\n";
                for (const auto& name : recipients) {
                    std::cout << "- " << name << "\n";
                }
                break;
            }
            case 4: {
                auto recipients = calculator.getNewScholarshipRecipients();
                std::cout << "New Scholarship Recipients (Top 40%):\n";
                for (const auto& name : recipients) {
                    std::cout << "- " << name << "\n";
                }
                break;
            }
            case 5:
                return;
            default:
                std::cout << "Invalid choice.\n";
            }
        }
    }

    void task5() {
        std::cout << "\n~~~ TASK 5: Word Grammar System.\n";

        Noun house("house");
        std::cout << "Original: " << house.getFullWord() << "\n";
        house.plural();
        std::cout << "Plural: " << house.getFullWord() << "\n";

        Verb go("go");
        std::cout << "Original: " << go.getFullWord() << "\n";
        go.third();
        std::cout << "Third person: " << go.getFullWord() << "\n";
        go.plural();
        std::cout << "Plural: " << go.getFullWord() << "\n";
        go.third();
        std::cout << "Third person plural: " << go.getFullWord() << "\n";

        Adjective happy("happy");
        std::cout << "Original: " << happy.getFullWord() << "\n";
        happy.comparative();
        std::cout << "Comparative: " << happy.getFullWord() << "\n";
        happy.superlative();
        std::cout << "Superlative: " << happy.getFullWord() << "\n";

        Noun child("child");
        std::cout << "Original: " << child.getFullWord() << "\n";
        child.changeCase("genitive");
        std::cout << "Genitive: " << child.getFullWord() << "\n";
    }

    void task6() {
        std::cout << "\n~~~ TASK 6: Geometric Shapes.\n";

        Rectangle rect(Point(0, 10), 5, 3);
        Triangle tri(Point(0, 0), 4, 45, 45);
        Ellipse ellipse(Point(0, 0), Point(2, 0), 3, 2);

        std::cout << "Rectangle:\n";
        std::cout << "- Area: " << rect.getArea() << "\n";
        std::cout << "- Perimeter: " << rect.getPerimeter() << "\n";
        std::cout << "- Center: (" << rect.getCenter().x << ", " << rect.getCenter().y << ")\n";

        std::cout << "Triangle:\n";
        std::cout << "- Area: " << tri.getArea() << "\n";
        std::cout << "- Perimeter: " << tri.getPerimeter() << "\n";
        std::cout << "- Center: (" << tri.getCenter().x << ", " << tri.getCenter().y << ")\n";

        std::cout << "Ellipse:\n";
        std::cout << "- Area: " << ellipse.getArea() << "\n";
        std::cout << "- Perimeter: " << ellipse.getPerimeter() << "\n";
        std::cout << "- Center: (" << ellipse.getCenter().x << ", " << ellipse.getCenter().y << ")\n";
    }

    void task7() {
        std::cout << "\n~~~ TASK 7: 2D Shapes.\n";

        Trapezoid trap(Point(0, 5), 3, 6, 4);
        Parallelogram para(Point(0, 5), 4, 3, 60);
        Circle circle(Point(0, 0), 5);

        std::vector<Shape2D*> shapes = { &trap, &para, &circle };

        double totalArea = 0;
        double totalPerimeter = 0;
        double maxArea = 0;

        for (auto shape : shapes) {
            totalArea += shape->getArea();
            totalPerimeter += shape->getPerimeter();
            if (shape->getArea() > maxArea) {
                maxArea = shape->getArea();
            }
        }

        std::cout << "Total Area: " << totalArea << "\n";
        std::cout << "Total Perimeter: " << totalPerimeter << "\n";
        std::cout << "Maximum Area: " << maxArea << "\n";
    }

    void task8() {
        std::cout << "\n~~~ TASK 8: Polygon System.\n";
        std::cout << "Polygon classes implemented in the system.\n";
    }

    void task9() {
        std::cout << "\n~~~ TASK 9: 3D Shapes.\n";

        Parallelepiped para(3, 4, 5);
        Pyramid3 pyr3(4, 6);
        Pyramid4 pyr4(3, 4, 5);

        std::vector<Shape3D*> shapes = { &para, &pyr3, &pyr4 };

        double totalVolume = 0;
        double totalSurfaceArea = 0;
        int totalVertices = 0;

        for (auto shape : shapes) {
            totalVolume += shape->getVolume();
            totalSurfaceArea += shape->getSurfaceArea();
            totalVertices += shape->getVertexCount();
        }

        std::cout << "Total Volume: " << totalVolume << "\n";
        std::cout << "Total Surface Area: " << totalSurfaceArea << "\n";
        std::cout << "Total Vertices: " << totalVertices << "\n";
    }

    void task10() {
        std::cout << "\n~~~ TASK 10: Equation System.\n";

        Equation linear(2, -4);
        QuadraticEquation quadratic(1, -3, 2);
        BiquadraticEquation biquad(1, -5, 4);

        std::cout << "Linear: ";
        linear.display();
        auto sol1 = linear.solve();
        std::cout << "\nSolutions: ";
        for (double s : sol1) std::cout << s << " ";

        std::cout << "\n\nQuadratic: ";
        quadratic.display();
        auto sol2 = quadratic.solve();
        std::cout << "\nSolutions: ";
        for (double s : sol2) std::cout << s << " ";

        std::cout << "\n\nBiquadratic: ";
        biquad.display();
        auto sol3 = biquad.solve();
        std::cout << "\nSolutions: ";
        for (double s : sol3) std::cout << s << " ";
        std::cout << "\n";
    }

    void task11() {
        std::cout << "\n~~~ TASK 11: Car Simulation.\n";

        Personal car1(50, 2);
        Truck truck1(100, 2);

        std::cout << "Personal car with 2 passengers:\n";
        std::cout << "Fuel per km: " << car1.fuelPerKm() << "L\n";
        bool canTravel1 = car1.go(200);
        std::cout << "Can travel 200km: " << (canTravel1 ? "Yes" : "No") << "\n";

        std::cout << "\nTruck with 2 tons cargo:\n";
        std::cout << "Fuel per km: " << truck1.fuelPerKm() << "L\n";
        bool canTravel2 = truck1.go(200);
        std::cout << "Can travel 200km: " << (canTravel2 ? "Yes" : "No") << "\n";
    }

    void task12() {
        std::cout << "\n~~~ TASK 12: Equation Root Finding.\n";

        LinearEquation linear(2, -4);
        CubicEquation cubic(1, 0, -2, 0);
        SineEquation sine(1, 1, 0);

        std::vector<EquationRoot*> equations = { &linear, &cubic, &sine };

        std::cout << "Equation Analysis:\n";
        for (auto eq : equations) {
            eq->display();
            std::cout << "\n";

            try {
                double root = eq->findRoot();
                std::cout << "Root found: " << root << "\n";
            }
            catch (const std::exception& e) {
                std::cout << "No root found: " << e.what() << "\n";
            }
            std::cout << "---\n";
        }
    }

    void task13() {
        std::cout << "\n~~~ TASK 13: Store System.\n";

        Store store;

        auto toy1 = std::make_shared<Toy>("Lego Set", "TOY001", "pcs", 49.99, "2024-01-15", 6);
        auto food1 = std::make_shared<Food>("Milk", "FOOD001", "liters", 2.99, "2024-01-10", 3);
        auto appliance1 = std::make_shared<Appliance>("Microwave", "APP001", "pcs", 199.99, "2024-01-01", true, 0);

        store.addProduct(toy1);
        store.addProduct(food1);
        store.addProduct(appliance1);

        std::cout << "All Products:\n";
        store.displayAllProducts();

        store.applyDiscounts();
        std::cout << "\nAfter applying discounts:\n";
        store.displayAllProducts();
    }

    void task14() {
        std::cout << "\n~~~ TASK 14: Address System.\n";

        std::vector<std::shared_ptr<Address>> addresses;

        addresses.push_back(std::make_shared<Address>("Kyiv", "Khreshchatyk", 1, 10));
        addresses.push_back(std::make_shared<InternationalAddress>("Kyiv", "Bohdana Khmelnytskoho", 15, 0, "Ukraine", "01001"));
        addresses.push_back(std::make_shared<Address>("Lviv", "Rynok Square", 1, 5));
        addresses.push_back(std::make_shared<InternationalAddress>("Kyiv", "Instytutska", 20, 3, "Ukraine", "01008"));

        std::map<std::string, int> cityCount;
        for (const auto& addr : addresses) {
            cityCount[addr->getCity()]++;
        }

        std::string mostPopularCity;
        int maxCount = 0;
        for (auto it = cityCount.begin(); it != cityCount.end(); ++it) {
            const std::string& city = it->first;
            int count = it->second;
            if (count > maxCount) {
                maxCount = count;
                mostPopularCity = city;
            }
        }

        std::cout << "Most popular city: " << mostPopularCity << " (appears " << maxCount << " times)\n";

        std::cout << "\nAddresses in " << mostPopularCity << ":\n";
        for (const auto& addr : addresses) {
            if (addr->getCity() == mostPopularCity) {
                addr->display();
                std::cout << "\n";
            }
        }
    }

    void task15() {
        std::cout << "\n~~~ TASK 15: Enhanced Person with Address.\n";

        std::vector<PersonWithEAddress> people;

        auto addr1 = std::make_shared<Address>("Kyiv", "Khreshchatyk", 1, 10);
        auto eaddr1 = EAddress("john@gmail.com", "", "+380501234567");
        people.emplace_back("John", "Doe", addr1, eaddr1);

        auto addr2 = std::make_shared<Address>("Kyiv", "Bohdana Khmelnytskoho", 15, 0);
        auto eaddr2 = EAddress("jane@gmail.com", "jane.com", "+380671234567");
        people.emplace_back("Jane", "Smith", addr2, eaddr2);

        auto addr3 = std::make_shared<Address>("Lviv", "Rynok Square", 1, 5);
        auto eaddr3 = EAddress("bob@yahoo.com", "", "+380631234567");
        people.emplace_back("Bob", "Johnson", addr3, eaddr3);

        std::cout << "People in Kyiv with gmail.com domain:\n";
        for (const auto& person : people) {
            if (person.getAddress()->getCity() == "Kyiv" &&
                person.getEAddress().getEmailDomain() == "gmail.com") {
                person.displayFull();
            }
        }
    }

    void task16() {
        std::cout << "\n~~~ TASK 16: Number System and Polynomials.\n";

        Polynomial poly;
        std::cout << "Enter polynomial details:\n";
        poly.input();

        std::cout << "Polynomial: ";
        poly.display();

        std::cout << "Choose evaluation point type (1 - Rational, 2 - Complex): ";
        int type;
        std::cin >> type;

        std::shared_ptr<Number> x;
        if (type == 1) {
            x = std::make_shared<RationalNumber>();
        }
        else {
            x = std::make_shared<ComplexNumber>();
        }
        std::cout << "Enter evaluation point:\n";
        x->input();

        try {
            auto result = poly.evaluate(x);
            std::cout << "Result at x = ";
            x->display();
            std::cout << " is ";
            result->display();
            std::cout << "\n";
        }
        catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }

    void displayMenu() {
        std::cout << "\n~~~ MAIN MENU ~~~\n";
        std::cout << "3. Ticket Office System\n";
        std::cout << "4. Student Scholarship System\n";
        std::cout << "5. Word Grammar System\n";
        std::cout << "6. Geometric Shapes (Rect, Tri, Ellipse)\n";
        std::cout << "7. 2D Shapes (Trap, Para, Circle)\n";
        std::cout << "8. Polygon System\n";
        std::cout << "9. 3D Shapes\n";
        std::cout << "10. Equation System\n";
        std::cout << "11. Car Simulation\n";
        std::cout << "12. Equation Root Finding\n";
        std::cout << "13. Store System\n";
        std::cout << "14. Address System\n";
        std::cout << "15. Enhanced Person with Address\n";
        std::cout << "16. Number System and Polynomials\n";
        std::cout << "17. Exit\n";
        std::cout << "Select an option (3-17): ";
    }

    void run() {
        while (true) {
            displayMenu();

            int choice = getValidatedInteger("");

            switch (choice) {
            case 3:
                task3();
                break;
            case 4:
                task4();
                break;
            case 5:
                task5();
                break;
            case 6:
                task6();
                break;
            case 7:
                task7();
                break;
            case 8:
                task8();
                break;
            case 9:
                task9();
                break;
            case 10:
                task10();
                break;
            case 11:
                task11();
                break;
            case 12:
                task12();
                break;
            case 13:
                task13();
                break;
            case 14:
                task14();
                break;
            case 15:
                task15();
                break;
            case 16:
                task16();
                break;
            case 17:
                std::cout << "Bye!\n";
                return;
            default:
                std::cout << "Invalid choice.\n";
            }

            std::cout << "\nPress Enter to continue...";
            clearInputBuffer();
            std::cin.get();
        }
    }
};

int main() {
    TaskManager manager;
    manager.run();
    return 0;
}