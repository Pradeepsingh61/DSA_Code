#include <iostream>
using namespace std;

inline double Area(double length, double breadth)
{
    return length * breadth;
}

int main() {
    double length, breadth;

    cout << "Enter length of room: ";
    cin >> length;

    cout << "Enter breadth of room: ";
    cin >> breadth;

    double area = Area(length, breadth);
    cout << "Area of room: " << area << " square units" << endl;

    return 0;
}