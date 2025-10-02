// This program provides an optimized implementation of the is_prime function
// and includes sample test cases as comments for quick reference.

#include <iostream>
#include <cmath>

/*
 * Function: is_prime
 * ------------------
 * Checks whether a given integer n is a prime number.
 *
 * n: the integer to check for primality.
 *
 * returns: true if n is prime, false otherwise.
 *
 * Time Complexity: O(sqrt(n))
 * - Only checks divisibility up to sqrt(n). If n = a * b,
 *   at least one of a or b must be <= sqrt(n), reducing iterations.
 * Space Complexity: O(1)
 */
bool is_prime(int n) {
    if (n <= 1) return false;          // 0 and 1 are not prime
    if (n <= 3) return true;           // 2 and 3 are prime
    if (n % 2 == 0 || n % 3 == 0)     // divisible by 2 or 3
        return false;

    // Only check numbers of form 6k ± 1 up to sqrt(n)
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

// Usage example with inline sample test cases
int main() {
    int numbers[] = {0, 1, 2, 3, 4, 5, 17, 20, 23, 25};

    for (int n : numbers) {
        if (is_prime(n))
            std::cout << n << " is a prime number." << std::endl;
        else
            std::cout << n << " is not a prime number." << std::endl;
    }

    return 0;
}

/*
Sample Test Cases:

Input Array: {0, 1, 2, 3, 4, 5, 17, 20, 23, 25}

Expected Output:
0 is not a prime number.
1 is not a prime number.
2 is a prime number.
3 is a prime number.
4 is not a prime number.
5 is a prime number.
17 is a prime number.
20 is not a prime number.
23 is a prime number.
25 is not a prime number.
*/
