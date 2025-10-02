/*
 * Fast Exponentiation Algorithm (Binary Exponentiation)
 * 
 * Description:
 * Fast Exponentiation is an efficient algorithm to calculate x^n using only O(log n) multiplications
 * instead of the naive O(n) approach. It works by decomposing the exponent into powers of 2
 * using the binary representation of the exponent.
 * 
 * The algorithm follows these steps:
 * 1. If n = 0, return 1 (any number raised to 0 is 1)
 * 2. If n is even, calculate x^(n/2) recursively and square the result
 * 3. If n is odd, calculate x^(n-1) and multiply by x
 * 
 * This implementation includes both recursive and iterative approaches, as well as
 * a modular version for calculating (x^n) % m efficiently.
 * 
 * Time Complexity: O(log n) where n is the exponent
 * Space Complexity: O(log n) for recursive approach, O(1) for iterative approach
 */

#include <iostream>
#include <cassert>

using namespace std;

// Recursive implementation of fast exponentiation
long long fastPowRecursive(long long x, long long n) {
    // Base cases
    if (n == 0) return 1;
    if (n == 1) return x;
    
    // Recursive case: calculate x^(n/2)
    long long half = fastPowRecursive(x, n / 2);
    
    // If n is even, return (x^(n/2))^2
    if (n % 2 == 0) {
        return half * half;
    }
    // If n is odd, return x * (x^(n/2))^2
    else {
        return x * half * half;
    }
}

// Iterative implementation of fast exponentiation
long long fastPowIterative(long long x, long long n) {
    // Base case
    if (n == 0) return 1;
    
    long long result = 1;
    
    // Process bits of n from right to left
    while (n > 0) {
        // If current bit is 1, multiply result by x
        if (n % 2 == 1) {
            result *= x;
        }
        
        // Square x for next bit
        x *= x;
        
        // Move to next bit
        n /= 2;
    }
    
    return result;
}

// Modular fast exponentiation: calculates (x^n) % m
long long fastPowMod(long long x, long long n, long long m) {
    // Base case
    if (n == 0) return 1;
    
    // Handle negative exponents
    if (n < 0) {
        // For simplicity, we don't handle negative exponents with modular arithmetic here
        // In a real implementation, you would need to calculate modular multiplicative inverse
        throw invalid_argument("Negative exponents not supported in modular exponentiation");
    }
    
    // Ensure x is within modulo range
    x %= m;
    
    long long result = 1;
    
    while (n > 0) {
        // If current bit is 1, multiply result by x
        if (n % 2 == 1) {
            result = (result * x) % m;
        }
        
        // Square x for next bit
        x = (x * x) % m;
        
        // Move to next bit
        n /= 2;
    }
    
    return result;
}

// Main function with test cases
int main() {
    // Test Case 1: Basic examples
    cout << "Test Case 1: Basic examples" << endl;
    cout << "2^10 = " << fastPowRecursive(2, 10) << " (Recursive)" << endl;
    cout << "2^10 = " << fastPowIterative(2, 10) << " (Iterative)" << endl;
    cout << "3^7 = " << fastPowRecursive(3, 7) << " (Recursive)" << endl;
    cout << "3^7 = " << fastPowIterative(3, 7) << " (Iterative)" << endl;
    cout << endl;
    
    // Test Case 2: Edge cases
    cout << "Test Case 2: Edge cases" << endl;
    cout << "Any number^0 = " << fastPowRecursive(5, 0) << endl;
    cout << "1^Any number = " << fastPowIterative(1, 100) << endl;
    cout << "0^5 = " << fastPowRecursive(0, 5) << endl;
    cout << endl;
    
    // Test Case 3: Modular exponentiation
    cout << "Test Case 3: Modular exponentiation" << endl;
    cout << "2^10 % 1000 = " << fastPowMod(2, 10, 1000) << endl;
    cout << "3^7 % 13 = " << fastPowMod(3, 7, 13) << endl;
    cout << "5^18 % 19 = " << fastPowMod(5, 18, 19) << endl;
    cout << endl;
    
    // Test Case 4: Large exponents (that would overflow with naive approach)
    cout << "Test Case 4: Large exponents" << endl;
    cout << "3^20 % 1000000007 = " << fastPowMod(3, 20, 1000000007) << endl;
    cout << "2^30 % 1000000007 = " << fastPowMod(2, 30, 1000000007) << endl;
    cout << endl;
    
    // Verification: Compare with built-in pow function for small values
    cout << "Verification with small values:" << endl;
    for (int i = 0; i <= 10; i++) {
        long long expected = 1;
        for (int j = 0; j < i; j++) expected *= 2;  // Calculate 2^i manually
        
        long long resultRecursive = fastPowRecursive(2, i);
        long long resultIterative = fastPowIterative(2, i);
        
        cout << "2^" << i << " = " << expected;
        assert(resultRecursive == expected);
        assert(resultIterative == expected);
        cout << " ✓" << endl;
    }
    
    return 0;
}