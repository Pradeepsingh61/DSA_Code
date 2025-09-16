#include <iostream>
using namespace std;

void printButterfly(int n) {
    // Upper part of the butterfly
    for (int i = 1; i <= n; i++) {
        // Print left stars
        for (int j = 1; j <= i; j++) {
            cout << "*";
        }
        // Print spaces
        for (int j = 1; j <= 2 * (n - i); j++) {
            cout << " ";
        }
        // Print right stars
        for (int j = 1; j <= i; j++) {
            cout << "*";
        }
        cout << endl;
    }

    // Lower part of the butterfly
    for (int i = n; i >= 1; i--) {
        // Print left stars
        for (int j = 1; j <= i; j++) {
            cout << "*";
        }
        // Print spaces
        for (int j = 1; j <= 2 * (n - i); j++) {
            cout << " ";
        }
        // Print right stars
        for (int j = 1; j <= i; j++) {
            cout << "*";
        }
        cout << endl;
    }
}

int main() {
    int n;
    cout << "Enter the number of rows for the butterfly pattern: ";
    cin >> n;

    printButterfly(n);

    return 0;
}