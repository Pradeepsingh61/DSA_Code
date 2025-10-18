/*
Algorithm Name
Large Factorial Calculation

Programming Language
C++

Category
Mathematical Algorithms

Difficulty Level
Medium (Intermediate)

Algorithm Description
The factorial of a number n! grows very quickly and cannot be stored in standard integer types for large n.

To handle large factorials:
If exact value is needed: store results in arrays or strings (simulate multiplication digit by digit).

If factorial modulo M is required: use iterative multiplication with modulus at each step.

For example: fact[n]=(fact[n−1]×n)%M
This ensures values don’t overflow and can handle very large n efficiently.

Applications include combinatorics, probability, cryptography, and modular arithmetic problems.

*/
#include <bits/stdc++.h>
using namespace std;

long long factorialMod(long long n, long long M) {
    long long fact = 1;
    for (long long i = 1; i <= n; i++) {
        fact = (fact * i) % M;
    }
    return fact;
}

int main() {
    long long n , M = 1000000007; // large n with prime modulus
    cin>>n;
    cout << "n! % M = " << factorialMod(n, M) << endl;
    return 0;
}

/*
Time Complexity: O(n)
Space Complexity:O(1)
*/
/*
Input
99

Output
n! % M = 104379182
*/
