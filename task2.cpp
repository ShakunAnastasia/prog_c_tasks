#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

class Point {
private:
    double x;
    double y;
    static int counter;

public:
    Point(double x_val = 0, double y_val = 0) : x(x_val), y(y_val) {
        counter++;
    }

    Point(const Point& other) : x(other.x), y(other.y) {
        counter++;
    }

    ~Point() {
        counter--;
    }

    double getX() const { return x; }
    double getY() const { return y; }

    void setX(double x_val) { x = x_val; }
    void setY(double y_val) { y = y_val; }

    static int getCounter() {
        return counter;
    }

    double distanceTo(const Point& other) const {
        double dx = x - other.x;
        double dy = y - other.y;
        return sqrt(dx * dx + dy * dy);
    }

    void inputFromTerminal() {
        cout << "Enter x coordinate: ";
        cin >> x;
        cout << "Enter y coordinate: ";
        cin >> y;
    }

    void display() const {
        cout << "(" << x << ", " << y << ")";
    }
};

int Point::counter = 0;

double calculatePerimeter(const vector<Point>& vertices) {
    if (vertices.size() < 3) {
        return 0.0;
    }

    double perimeter = 0.0;
    int n = vertices.size();

    for (int i = 0; i < n; i++) {
        Point current = vertices[i];
        Point next = vertices[(i + 1) % n];
        perimeter += current.distanceTo(next);
    }

    return perimeter;
}

void displayPolygonInfo(const vector<Point>& vertices) {
    cout << "\nPolygon information" << endl;
    cout << "Number of vertices: " << vertices.size() << endl;

    cout << "Vertices: ";
    for (size_t i = 0; i < vertices.size(); ++i) {
        vertices[i].display();
        if (i < vertices.size() - 1) {
            cout << " -> ";
        }
    }
    cout << endl;

    double perimeter = calculatePerimeter(vertices);
    cout << "Perimeter: " << perimeter << endl;

    cout << "Static counter value: " << Point::getCounter() << " points created" << endl;
}

int main() {
    vector<Point> vertices;
    string response;

    cout << "Polygon creation" << endl;

    do {
        cout << "\nAdd vertex? (yes/no): ";
        cin >> response;

        if (response == "yes" || response == "y" || response == "Yes" || response == "Y") {
            Point newPoint;
            newPoint.inputFromTerminal();
            vertices.push_back(newPoint);

            cout << "Vertex added: ";
            newPoint.display();
            cout << endl;

            cout << "Total vertices so far: " << vertices.size() << endl;
            cout << "Static counter: " << Point::getCounter() << " points" << endl;
        }

    } while (response == "yes" || response == "y" || response == "Yes" || response == "Y");

    if (vertices.size() < 3) {
        cout << "\nError: A polygon must have at least 3 vertices!" << endl;
        cout << "You entered only " << vertices.size() << " vertices." << endl;
        return 1;
    }

    displayPolygonInfo(vertices);

    cout << "\nDemonstrating static counter" << endl;
    cout << "Current counter: " << Point::getCounter() << endl;

    {
        Point temp1(1, 1);
        Point temp2(2, 2);
        cout << "After creating 2 temporary points: " << Point::getCounter() << endl;
    }

    cout << "After temporary points are destroyed: " << Point::getCounter() << endl;

    return 0;
}