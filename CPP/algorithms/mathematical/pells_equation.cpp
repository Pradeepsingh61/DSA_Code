// File: pells_equation.cpp
// Solve Pell's Equation: x^2 - D*y^2 = 1
// Contributed for Hacktoberfest 2025

#include <bits/stdc++.h>
using namespace std;

// Function to find fundamental solution of Pell's equation
pair<long long, long long> solvePell(int D) {
    int a0 = sqrt(D);
    if (a0 * a0 == D) {
        throw invalid_argument("D must be non-square!");
    }

    int m = 0, d = 1, a = a0;

    long long num1 = 1, num2 = a;
    long long den1 = 0, den2 = 1;

    // Continue until x^2 - D*y^2 = 1
    while (true) {
        m = d * a - m;
        d = (D - m * m) / d;
        a = (a0 + m) / d;

        long long num = a * num2 + num1;
        long long den = a * den2 + den1;

        num1 = num2; num2 = num;
        den1 = den2; den2 = den;

        if (num * num - 1LL * D * den * den == 1) {
            return {num, den}; // fundamental solution (x, y)
        }
    }
}

int main() {
    int D;
    cout << "Enter a non-square positive integer D: ";
    cin >> D;

    try {
        auto sol = solvePell(D);
        cout << "Fundamental solution to x^2 - " << D << "*y^2 = 1:\n";
        cout << "x = " << sol.first << ", y = " << sol.second << "\n";
    } catch (invalid_argument &e) {
        cout << e.what() << "\n";
    }

    return 0;
}
