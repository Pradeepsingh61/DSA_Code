/*
 * Derangements Calculation using Inclusion-Exclusion Principle
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
#include <atcoder/modint>  // AtCoder library for modular arithmetic
#include <bits/stdc++.h>   // Includes all standard C++ libraries (not best practice, but convenient for contests)

using namespace std;
using mint = atcoder::modint;  // Define a shorthand alias "mint" for the modint type

int main() {
    int n, m;
    cin >> n >> m;  // Read n (limit of loop) and m (modulus)
    
    mint::set_mod(m);  // Set the modulus dynamically (since m can vary per test case)

    mint c = 1;  // Initialize modular variable c = 1
    for (int i = 1; i <= n; i++) {
        // Multiply c by i, then add or subtract 1 depending on whether i is odd or even
        // If i is odd: add -1 (i.e., subtract 1)
        // If i is even: add +1
        c = (c * i) + (i % 2 == 1 ? -1 : 1);

        // Output the current value of c modulo m
        cout << c.val() << ' ';
    }
    cout << endl;
}
