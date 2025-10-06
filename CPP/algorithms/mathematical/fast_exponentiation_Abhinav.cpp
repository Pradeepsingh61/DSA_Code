/*
Algorithm Name
Fast Exponentiation

Programming Language
C++

Category
Mathematical Algorithms

Difficulty Level
Medium (Intermediate)

Algorithm Description
Fast exponentiation is an efficient method to compute powers of a number a^b in logarithmic time. Instead of multiplying a repeatedly b times (which takes O(b)), it reduces the problem size by half at each step.

If the exponent is even: a^b = (a^(b/2))^2

If the exponent is odd: a^b = a * a^(b-1)

Time Complexity: O(logb)
Space Complexity: O(logb) (recursive) or O(1) (iterative)

*/

#include <bits/stdc++.h>
using namespace std;

// Recursive method
long long power_recursive(long long a, long long b) {
    if (b == 0) return 1;
    if (b % 2 == 0) {
        long long half = power_recursive(a, b / 2);
        return half * half;
    } else {
        return a * power_recursive(a, b - 1);
    }
}

// Iterative method (better for large b)
long long power_iterative(long long a, long long b) {
    long long result = 1, base = a;
    while (b > 0) {
        if (b % 2 == 1) result *= base;
        base *= base;
        b /= 2;
    }
    return result;
}

int main() {
    cout << power_recursive(2, 10) << endl; // 1024
    cout << power_iterative(3, 13) << endl; // 1594323
    return 0;
}

/*
Time Complexity: O(log b)

Space Complexity:
Recursive: O(log b) (stack calls)

Iterative: O(1)
*/

/*
Output
1024
1594323
*/
