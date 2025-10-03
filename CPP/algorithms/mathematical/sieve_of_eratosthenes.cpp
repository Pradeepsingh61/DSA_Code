/*
 * Sieve of Eratosthenes Algorithm
 * 
 * Description:
 * The Sieve of Eratosthenes is an ancient algorithm for finding all prime numbers up to a specified limit.
 * It works by iteratively marking the multiples of each prime, starting from 2.
 * The algorithm follows these steps:
 * 1. Create a list of consecutive integers from 2 to n: (2, 3, 4, ..., n)
 * 2. Start with the first prime number, p = 2
 * 3. Mark all multiples of p that are greater than p (i.e., 2p, 3p, 4p, ...) as composite (not prime)
 * 4. Find the smallest number greater than p that is not marked. If no such number exists, stop
 * 5. Set p to this new number (which is the next prime) and repeat from step 3
 * 
 * Time Complexity: O(n log log n) where n is the upper limit
 * Space Complexity: O(n) for storing the sieve array
 */

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Function to find all prime numbers up to limit using Sieve of Eratosthenes
vector<int> sieveOfEratosthenes(int n) {
    // Create a boolean array "isPrime[0..n]" and initialize all entries as true
    vector<bool> isPrime(n + 1, true);
    
    // 0 and 1 are not prime numbers
    if (n >= 0) isPrime[0] = false;
    if (n >= 1) isPrime[1] = false;
    
    // Iterate through all numbers up to sqrt(n)
    for (int p = 2; p * p <= n; p++) {
        // If isPrime[p] is not changed, then it is a prime
        if (isPrime[p]) {
            // Update all multiples of p as not prime
            for (int i = p * p; i <= n; i += p) {
                isPrime[i] = false;
            }
        }
    }
    
    // Create a vector to store all prime numbers
    vector<int> primes;
    for (int p = 2; p <= n; p++) {
        if (isPrime[p]) {
            primes.push_back(p);
        }
    }
    
    return primes;
}

// Function to print a vector of integers
void printVector(const vector<int>& vec, const string& label) {
    cout << label << ": ";
    for (size_t i = 0; i < vec.size(); i++) {
        cout << vec[i];
        if (i < vec.size() - 1) {
            cout << ", ";
        }
    }
    cout << endl;
}

// Function to count primes up to n (for comparison with optimized sieve)
int countPrimes(int n) {
    vector<int> primes = sieveOfEratosthenes(n);
    return primes.size();
}

// Main function with test cases
int main() {
    // Test Case 1: Small range
    cout << "Test Case 1: Primes up to 30" << endl;
    vector<int> primes1 = sieveOfEratosthenes(30);
    printVector(primes1, "Prime numbers");
    cout << "Count: " << primes1.size() << endl << endl;
    
    // Test Case 2: Medium range
    cout << "Test Case 2: Primes up to 100" << endl;
    vector<int> primes2 = sieveOfEratosthenes(100);
    printVector(primes2, "Prime numbers");
    cout << "Count: " << primes2.size() << endl << endl;
    
    // Test Case 3: Larger range (only count, not print)
    cout << "Test Case 3: Count of primes up to 1000" << endl;
    int count3 = countPrimes(1000);
    cout << "Count: " << count3 << endl << endl;
    
    // Test Case 4: Edge cases
    cout << "Test Case 4: Edge cases" << endl;
    vector<int> primes4a = sieveOfEratosthenes(1);
    printVector(primes4a, "Primes up to 1");
    
    vector<int> primes4b = sieveOfEratosthenes(2);
    printVector(primes4b, "Primes up to 2");
    
    // Performance demonstration for larger numbers
    cout << endl << "Performance demonstration:" << endl;
    cout << "Count of primes up to 10,000: " << countPrimes(10000) << endl;
    cout << "Count of primes up to 100,000: " << countPrimes(100000) << endl;
    
    return 0;
}