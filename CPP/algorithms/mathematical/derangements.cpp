/*
 * Derangements Calculation using Inclusion-Exclusion Principle
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
#include <iostream>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;  // Read n (limit) and m (modulus)

    long long c = 1;  // Initialize c = 1 (use long long to avoid overflow before mod)
    for (int i = 1; i <= n; i++) {
        // Multiply c by i under modulo m
        c = (c * i) % m;

        // Add or subtract 1 depending on whether i is odd or even
        if (i % 2 == 1) c = (c - 1 + m) % m;  // subtract 1 safely under mod
        else c = (c + 1) % m;                 // add 1 safely under mod

        cout << c << ' ';
    }
    cout << endl;
    return 0;
}
