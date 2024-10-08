#include<iostream>
using namespace std;

class Distance {
    private:
    double meters;

    public:
    Distance() {
        meters = 0;
    }

    void set_data(double x) {
        meters = x;
    }

    void display() {
        cout << "The current value is: " << meters << endl;
    }

    friend void add(Distance &b);
};

void add(Distance &b) {
    cout << "Enter the value:" << endl;
    double a;
    cin >> a;
    b.meters += a;
    cout << "Final value: " << b.meters << endl;
}

int main() {
    Distance box;
    box.set_data(12);
    box.display();

    add(box);

    return 0;
}
