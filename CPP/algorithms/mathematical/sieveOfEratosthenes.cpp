/*
Algorithm Name
Sieve of Eratosthenes

Programming Language
C++

Category
Mathematical Algorithms

Difficulty Level
Medium (Intermediate)

Algorithm Description
The Sieve of Eratosthenes is an efficient algorithm to find all prime numbers up to a given limit n. It works by iteratively marking the multiples of each prime number starting from 2.

Steps:

Create a boolean array isPrime[0..n] and initialize all entries as true.

Set isPrime[0] and isPrime[1] to false since 0 and 1 are not prime.

For each number p from 2 to sqrt(n):

If isPrime[p] is true, mark all multiples of p greater than or equal to p*p as false.

All numbers that remain true in the isPrime array are prime numbers.

Time Complexity: O(n log log n) – very efficient for generating primes up to large n.
Space Complexity: O(n) – for the boolean array.

*/
#include <bits/stdc++.h>
using namespace std;

vector<int> sieveOfEratosthenes(int n) {
    vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false;

    for (int p = 2; p * p <= n; p++) {
        if (isPrime[p]) {
            for (int i = p * p; i <= n; i += p)
                isPrime[i] = false;
        }
    }

    vector<int> primes;
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) primes.push_back(i);
    }
    return primes;
}

int main() {
    int n;
    cin>>n;
    vector<int> primes = sieveOfEratosthenes(n);
    cout << "Primes up to " << n << ": ";
    for (int p : primes) cout << p << " ";
    cout << endl;
    return 0;
}

/*
Time Complexity: 
𝑂O(nloglogn)

Space Complexity: 
O(n)*/

/*
Input 
100

Output
Primes up to 100: 2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 73 79 83 89 97 
*/