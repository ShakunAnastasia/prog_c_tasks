#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <limits>

using namespace std;

// Task 1

class Person {
protected:
    string name;
    unsigned byear;
public:
    Person() : name(""), byear(0) {}
    Person(const string& n, unsigned y) : name(n), byear(y) {}

    virtual int input() {
        cout << "Enter surname: ";
        cin >> name;
        cout << "Enter birth year: ";
        cin >> byear;
        return 1;
    }

    virtual void show() const {
        cout << "Surname: " << name << ", Birth year: " << byear;
    }

    friend ostream& operator<<(ostream& os, const Person& p) {
        p.show();
        return os;
    }

    friend istream& operator>>(istream& is, Person& p) {
        cout << "Enter surname: ";
        is >> p.name;
        cout << "Enter birth year: ";
        is >> p.byear;
        return is;
    }

    string getName() const { return name; }
    unsigned getBirthYear() const { return byear; }

    virtual ~Person() {}
};

class Friend : public Person {
private:
    string phone;
public:
    Friend() : Person(), phone("") {}
    Friend(const string& n, unsigned y, const string& p) : Person(n, y), phone(p) {}

    int input() override {
        Person::input();
        cout << "Enter phone number: ";
        cin >> phone;
        return 1;
    }

    void show() const override {
        Person::show();
        cout << ", Phone: " << phone;
    }

    friend ostream& operator<<(ostream& os, const Friend& f) {
        f.show();
        return os;
    }

    friend istream& operator>>(istream& is, Friend& f) {
        is >> static_cast<Person&>(f);
        cout << "Enter phone number: ";
        is >> f.phone;
        return is;
    }

    string getPhone() const { return phone; }
    void setPhone(const string& p) { phone = p; }
};

class PhoneBook {
private:
    vector<Friend> friends;
    string filename;
    static const int MAX_SIZE = 100;

public:
    PhoneBook(const string& fname = "phonebook.txt") : filename(fname) {
        loadFromFile();
    }

    void createBook() {
        friends.clear();
        cout << "New phone book created." << endl;
    }

    void addFriend() {
        if (friends.size() >= MAX_SIZE) {
            cout << "Phone book is full! Maximum " << MAX_SIZE << " friends allowed." << endl;
            return;
        }

        Friend f;
        if (f.input()) {
            for (const auto& existing : friends) {
                if (existing.getName() == f.getName()) {
                    cout << "Friend with this name already exists!" << endl;
                    return;
                }
            }
            friends.push_back(f);
            saveToFile();
            cout << "Friend added successfully!" << endl;
        }
    }

    string findPhoneByName(const string& name) {
        for (const auto& f : friends) {
            if (f.getName() == name) {
                return f.getPhone();
            }
        }
        return "Not found";
    }

    bool changePhone(const string& name, const string& newPhone) {
        for (auto& f : friends) {
            if (f.getName() == name) {
                f.setPhone(newPhone);
                saveToFile();
                return true;
            }
        }
        return false;
    }

    void displayAll() {
        if (friends.empty()) {
            cout << "Phone book is empty." << endl;
            return;
        }

        cout << "Phone Book Contents:" << endl;
        for (size_t i = 0; i < friends.size(); ++i) {
            cout << i + 1 << ". " << friends[i] << endl;
        }
    }

private:
    void loadFromFile() {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Could not open file " << filename << ". Starting with empty phone book." << endl;
            return;
        }

        friends.clear();
        string line;
        while (getline(file, line) && friends.size() < MAX_SIZE) {
            istringstream iss(line);
            string name, phone;
            unsigned year;

            if (iss >> name >> year >> phone) {
                friends.emplace_back(name, year, phone);
            }
        }
        file.close();
        cout << "Loaded " << friends.size() << " friends from file." << endl;
    }

    void saveToFile() {
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Could not save to file " << filename << endl;
            return;
        }

        for (const auto& f : friends) {
            file << f.getName() << " " << f.getBirthYear() << " " << f.getPhone() << endl;
        }
        file.close();
    }
};

// Task 2

class Point {
protected:
    double x, y;
    int dimension;
public:
    Point(double x = 0, double y = 0) : x(x), y(y), dimension(2) {}

    virtual void input() {
        cout << "Enter x coordinate: ";
        cin >> x;
        cout << "Enter y coordinate: ";
        cin >> y;
        dimension = 2;
    }

    virtual void show() const {
        cout << "(" << x << ", " << y << ")";
    }

    double getX() const { return x; }
    double getY() const { return y; }
    int getDimension() const { return dimension; }

    virtual double distanceTo(const Point& other) const {
        return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
    }

    virtual ~Point() {}
};

class Point3D : public Point {
private:
    double z;
public:
    Point3D(double x = 0, double y = 0, double z = 0) : Point(x, y), z(z) {
        dimension = 3;
    }

    void input() override {
        Point::input();
        cout << "Enter z coordinate: ";
        cin >> z;
        dimension = 3;
    }

    void show() const override {
        cout << "(" << x << ", " << y << ", " << z << ")";
    }

    double getZ() const { return z; }

    double distanceTo(const Point& other) const override {
        if (const Point3D* other3D = dynamic_cast<const Point3D*>(&other)) {
            return sqrt(pow(x - other3D->x, 2) + pow(y - other3D->y, 2) + pow(z - other3D->z, 2));
        }
        else {
            // If other is 2D point, treat z as 0
            return sqrt(pow(x - other.getX(), 2) + pow(y - other.getY(), 2) + pow(z, 2));
        }
    }
};

class Segment {
private:
    Point* start;
    Point* end;
    bool ownsPoints;

public:
    Segment(Point* s, Point* e, bool own = true) : start(s), end(e), ownsPoints(own) {}

    Segment(double x1, double y1, double x2, double y2) : ownsPoints(true) {
        start = new Point(x1, y1);
        end = new Point(x2, y2);
    }

    Segment(double x1, double y1, double z1, double x2, double y2, double z2) : ownsPoints(true) {
        start = new Point3D(x1, y1, z1);
        end = new Point3D(x2, y2, z2);
    }

    void input() {
        cout << "Enter start point:" << endl;
        start->input();
        cout << "Enter end point:" << endl;
        end->input();
    }

    void show() const {
        cout << "Segment: ";
        start->show();
        cout << " to ";
        end->show();
        cout << endl;
    }

    double length() const {
        return start->distanceTo(*end);
    }

    int getDimension() const {
        return max(start->getDimension(), end->getDimension());
    }

    static bool doIntersect2D(const Segment& s1, const Segment& s2) {
        if (s1.getDimension() > 2 || s2.getDimension() > 2) {
            cout << "Intersection check available only for 2D segments." << endl;
            return false;
        }

        auto orientation = [](const Point& p, const Point& q, const Point& r) -> int {
            double val = (q.getY() - p.getY()) * (r.getX() - q.getX()) -
                (q.getX() - p.getX()) * (r.getY() - q.getY());
            if (val == 0) return 0;
            return (val > 0) ? 1 : 2;
            };

        auto onSegment = [](const Point& p, const Point& q, const Point& r) -> bool {
            return (q.getX() <= max(p.getX(), r.getX()) && q.getX() >= min(p.getX(), r.getX()) &&
                q.getY() <= max(p.getY(), r.getY()) && q.getY() >= min(p.getY(), r.getY()));
            };

        const Point& p1 = *s1.start;
        const Point& q1 = *s1.end;
        const Point& p2 = *s2.start;
        const Point& q2 = *s2.end;

        int o1 = orientation(p1, q1, p2);
        int o2 = orientation(p1, q1, q2);
        int o3 = orientation(p2, q2, p1);
        int o4 = orientation(p2, q2, q1);

        if (o1 != o2 && o3 != o4) return true;

        if (o1 == 0 && onSegment(p1, p2, q1)) return true;
        if (o2 == 0 && onSegment(p1, q2, q1)) return true;
        if (o3 == 0 && onSegment(p2, p1, q2)) return true;
        if (o4 == 0 && onSegment(p2, q1, q2)) return true;

        return false;
    }

    ~Segment() {
        if (ownsPoints) {
            delete start;
            delete end;
        }
    }
};

// Main menu
void task1_menu() {
    PhoneBook pb;
    int choice;

    do {
        cout << "\n~~~ PHONE BOOK MENU ~~~" << endl;
        cout << "1. Create new phone book" << endl;
        cout << "2. Add friend" << endl;
        cout << "3. Find phone by name" << endl;
        cout << "4. Change phone number" << endl;
        cout << "5. Display all friends" << endl;
        cout << "0. Back to main menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            pb.createBook();
            break;
        case 2:
            pb.addFriend();
            break;
        case 3: {
            string name;
            cout << "Enter name to search: ";
            cin >> name;
            string phone = pb.findPhoneByName(name);
            if (phone != "Not found") {
                cout << "Phone number: " << phone << endl;
            }
            else {
                cout << "Friend not found!" << endl;
            }
            break;
        }
        case 4: {
            string name, newPhone;
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter new phone number: ";
            cin >> newPhone;
            if (pb.changePhone(name, newPhone)) {
                cout << "Phone number updated successfully!" << endl;
            }
            else {
                cout << "Friend not found!" << endl;
            }
            break;
        }
        case 5:
            pb.displayAll();
            break;
        case 0:
            cout << "Returning to main menu..." << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
        }
    } while (choice != 0);
}

void task2_menu() {
    int choice;

    do {
        cout << "\n~~~ GEOMETRY MENU ~~~" << endl;
        cout << "1. Work with 2D points and segments" << endl;
        cout << "2. Work with 3D points and segments" << endl;
        cout << "3. Check if two 2D segments intersect" << endl;
        cout << "0. Back to main menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            Point p1, p2;
            cout << "Enter first 2D point:" << endl;
            p1.input();
            cout << "Enter second 2D point:" << endl;
            p2.input();

            Segment seg(&p1, &p2, false);
            seg.show();
            cout << "Segment length: " << seg.length() << endl;
            break;
        }
        case 2: {
            Point3D p1, p2;
            cout << "Enter first 3D point:" << endl;
            p1.input();
            cout << "Enter second 3D point:" << endl;
            p2.input();

            Segment seg(&p1, &p2, false);
            seg.show();
            cout << "Segment length: " << seg.length() << endl;
            break;
        }
        case 3: {
            cout << "Enter first segment (2D):" << endl;
            Point p1, p2;
            cout << "First point:" << endl;
            p1.input();
            cout << "Second point:" << endl;
            p2.input();
            Segment seg1(&p1, &p2, false);

            cout << "Enter second segment (2D):" << endl;
            Point p3, p4;
            cout << "First point:" << endl;
            p3.input();
            cout << "Second point:" << endl;
            p4.input();
            Segment seg2(&p3, &p4, false);

            if (Segment::doIntersect2D(seg1, seg2)) {
                cout << "Segments intersect!" << endl;
            }
            else {
                cout << "Segments do not intersect!" << endl;
            }
            break;
        }
        case 0:
            cout << "Returning to main menu..." << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
        }
    } while (choice != 0);
}

void displayMainMenu() {
    cout << "~~~ MAIN MENU ~~~" << endl;
    cout << "1. Phone Book System" << endl;
    cout << "2. Geometry System" << endl;
    cout << "0. Exit" << endl;
    cout << "~~~" << endl;
    cout << "Enter your choice (0-2): ";
}

int main() {
    int choice;

    do {
        displayMainMenu();
        cin >> choice;

        try {
            switch (choice) {
            case 1:
                task1_menu();
                break;
            case 2:
                task2_menu();
                break;
            case 0:
                cout << "Bye!" << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
                break;
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