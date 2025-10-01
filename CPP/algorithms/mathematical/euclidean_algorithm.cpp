/*
 * Algorithm: Euclidean Algorithm for GCD
 * Description: The Euclidean algorithm is an efficient method to compute the greatest common divisor (GCD) of two integers.
 *              It's based on the principle that if a and b are two positive integers, then gcd(a,b) = gcd(b, a mod b).
 * Time Complexity: O(log(min(a,b)))
 * Space Complexity: O(log(min(a,b))) for recursive approach, O(1) for iterative approach
 * Author: Abhiram
 */

#include <iostream>

// Recursive implementation of the Euclidean Algorithm
int gcdRecursive(int a, int b) {
    // Base case
    if (b == 0)
        return a;
    
    // Recursive case: gcd(a,b) = gcd(b, a mod b)
    return gcdRecursive(b, a % b);
}

// Iterative implementation of the Euclidean Algorithm
int gcdIterative(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Extended Euclidean Algorithm to find coefficients x and y such that ax + by = gcd(a,b)
void extendedGCD(int a, int b, int &x, int &y, int &gcd) {
    // Base case
    if (b == 0) {
        x = 1;
        y = 0;
        gcd = a;
        return;
    }
    
    // Recursive call
    int x1, y1;
    extendedGCD(b, a % b, x1, y1, gcd);
    
    // Update x and y using results of recursive call
    x = y1;
    y = x1 - (a / b) * y1;
}

int main() {
    int a, b;
    std::cout << "Enter two positive integers: ";
    std::cin >> a >> b;
    
    // Ensure positive integers
    a = abs(a);
    b = abs(b);
    
    // Calculate GCD using both methods
    std::cout << "GCD using recursive Euclidean algorithm: " << gcdRecursive(a, b) << std::endl;
    std::cout << "GCD using iterative Euclidean algorithm: " << gcdIterative(a, b) << std::endl;
    
    // Calculate coefficients using Extended Euclidean algorithm
    int x, y, gcd;
    extendedGCD(a, b, x, y, gcd);
    std::cout << "Extended Euclidean Algorithm results:" << std::endl;
    std::cout << "GCD: " << gcd << std::endl;
    std::cout << "Coefficients x and y: " << x << " and " << y << std::endl;
    std::cout << "Verification: " << a << " * " << x << " + " << b << " * " << y << " = " << (a*x + b*y) << std::endl;
    
    return 0;
}
