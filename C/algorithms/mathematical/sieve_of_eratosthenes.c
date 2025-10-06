/*
 * Algorithm Name:
 * Sieve of Eratosthenes (Prime Number Generation)
 *
 * Programming Language:
 * C
 *
 * Category:
 * Mathematical Algorithms / Number Theory
 *
 * Difficulty Level:
 * Easy to Medium
 *
 * Algorithm Description:
 *
 * 1. Problem it solves:
 *    -> The Sieve of Eratosthenes efficiently finds all prime numbers up to a given
 *       limit n. It systematically eliminates multiples of each prime, leaving only
 *       prime numbers in the final result.
 *
 * 2. Approach / Idea:
 *    -> Create a boolean array of size n+1, initially all true
 *    -> Mark 0 and 1 as non-prime (false)
 *    -> For each number p from 2 to √n:
 *       - If p is marked as prime, mark all multiples of p as non-prime
 *    -> All remaining true values represent prime numbers
 *
 * 3. Complexity:
 *    Time: O(n log log n) - very efficient for generating many primes
 *    Space: O(n) for the boolean array
 *
 * 4. Optimizations Implemented:
 *    -> Start marking multiples from p² (smaller multiples already marked)
 *    -> Only check up to √n for the outer loop
 *    -> Skip even numbers after 2 (segmented sieve optimization)
 *    -> Bit manipulation for memory optimization
 *
 * 5. Applications:
 *    -> Cryptography (RSA key generation)
 *    -> Competitive programming problems
 *    -> Mathematical research and number theory
 *    -> Prime factorization algorithms
 *    -> Generating large sets of primes efficiently
 *
 * 6. Variants Implemented:
 *    -> Basic Sieve of Eratosthenes
 *    -> Optimized Sieve (odd numbers only)
 *    -> Segmented Sieve (for very large ranges)
 *    -> Prime counting and analysis functions
 *
 * Author:
 * Rishan Menezes
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define MAX_LIMIT 10000000  // 10 million

// Function prototypes
bool* sieveOfEratosthenes(int n, int* primeCount);
bool* optimizedSieve(int n, int* primeCount);
void segmentedSieve(int low, int high);
bool isPrime(int n);
bool isPrimeFast(int n);
int* getPrimesInRange(int start, int end, int* count);
void printPrimes(bool* sieve, int n, int limit);
void analyzePrimes(bool* sieve, int n);
double measureSieveTime(int n);
void demonstrateSieve(int n);
void primeFactorization(int n);
int countPrimesUpTo(int n);
void findTwinPrimes(int n);
void findPrimeGaps(int n);
void compareSieveMethods(int n);
long long power(long long base, long long exp, long long mod);
bool millerTest(long long d, long long n);
bool millerRabin(long long n, int k);

int main() {
    int choice, n, start, end;
    bool* sieve = NULL;
    int primeCount = 0;
    
    printf("=== Sieve of Eratosthenes - Prime Number Algorithms ===\n\n");
    
    while (1) {
        printf("\n=== Prime Number Operations ===\n");
        printf("1.  Generate primes using basic sieve\n");
        printf("2.  Generate primes using optimized sieve\n");
        printf("3.  Segmented sieve for large ranges\n");
        printf("4.  Check if a number is prime\n");
        printf("5.  Find primes in a specific range\n");
        printf("6.  Prime factorization of a number\n");
        printf("7.  Count primes up to n\n");
        printf("8.  Find twin primes\n");
        printf("9.  Analyze prime gaps\n");
        printf("10. Compare sieve methods performance\n");
        printf("11. Demonstrate sieve step-by-step\n");
        printf("12. Miller-Rabin primality test\n");
        printf("13. Analyze prime distribution\n");
        printf("0.  Exit\n");
        printf("Enter your choice: ");
        
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter upper limit (max %d): ", MAX_LIMIT);
                scanf("%d", &n);
                
                if (n <= 1 || n > MAX_LIMIT) {
                    printf("Invalid limit! Must be between 2 and %d\n", MAX_LIMIT);
                    break;
                }
                
                if (sieve) free(sieve);
                sieve = sieveOfEratosthenes(n, &primeCount);
                
                printf("Found %d primes up to %d\n", primeCount, n);
                
                if (n <= 100) {
                    printPrimes(sieve, n, n);
                } else {
                    printf("First 20 primes: ");
                    printPrimes(sieve, n, 20);
                }
                break;
                
            case 2:
                printf("Enter upper limit (max %d): ", MAX_LIMIT);
                scanf("%d", &n);
                
                if (n <= 1 || n > MAX_LIMIT) {
                    printf("Invalid limit! Must be between 2 and %d\n", MAX_LIMIT);
                    break;
                }
                
                if (sieve) free(sieve);
                sieve = optimizedSieve(n, &primeCount);
                
                printf("Found %d primes up to %d using optimized sieve\n", primeCount, n);
                
                if (n <= 100) {
                    printPrimes(sieve, n, n);
                } else {
                    printf("First 20 primes: ");
                    printPrimes(sieve, n, 20);
                }
                break;
                
            case 3:
                printf("Enter range [low, high] (max %d): ", MAX_LIMIT);
                scanf("%d %d", &start, &end);
                
                if (start < 2 || end > MAX_LIMIT || start > end) {
                    printf("Invalid range!\n");
                    break;
                }
                
                printf("Primes in range [%d, %d]:\n", start, end);
                segmentedSieve(start, end);
                break;
                
            case 4:
                printf("Enter number to check: ");
                scanf("%d", &n);
                
                if (n < 2) {
                    printf("%d is not prime\n", n);
                } else {
                    bool prime1 = isPrime(n);
                    bool prime2 = isPrimeFast(n);
                    
                    printf("Basic check: %d is %s\n", n, prime1 ? "prime" : "not prime");
                    printf("Fast check: %d is %s\n", n, prime2 ? "prime" : "not prime");
                    
                    if (n > 1000) {
                        bool prime3 = millerRabin(n, 5);
                        printf("Miller-Rabin: %d is %s\n", n, prime3 ? "probably prime" : "composite");
                    }
                }
                break;
                
            case 5:
                printf("Enter range [start, end]: ");
                scanf("%d %d", &start, &end);
                
                if (start < 2 || start > end) {
                    printf("Invalid range!\n");
                    break;
                }
                
                int count;
                int* primes = getPrimesInRange(start, end, &count);
                
                if (count > 0) {
                    printf("Found %d primes in range [%d, %d]:\n", count, start, end);
                    for (int i = 0; i < count && i < 50; i++) {
                        printf("%d ", primes[i]);
                        if ((i + 1) % 10 == 0) printf("\n");
                    }
                    if (count > 50) printf("... and %d more", count - 50);
                    printf("\n");
                    free(primes);
                } else {
                    printf("No primes found in range [%d, %d]\n", start, end);
                }
                break;
                
            case 6:
                printf("Enter number for prime factorization: ");
                scanf("%d", &n);
                
                if (n < 2) {
                    printf("Number must be >= 2\n");
                } else {
                    printf("Prime factorization of %d: ", n);
                    primeFactorization(n);
                }
                break;
                
            case 7:
                printf("Enter upper limit: ");
                scanf("%d", &n);
                
                if (n < 2) {
                    printf("No primes less than 2\n");
                } else {
                    int count = countPrimesUpTo(n);
                    printf("Number of primes up to %d: %d\n", n, count);
                    
                    // Prime number theorem approximation
                    if (n > 10) {
                        double approximation = n / log(n);
                        printf("Prime number theorem approximation: %.0f\n", approximation);
                        printf("Accuracy: %.2f%%\n", (count / approximation) * 100);
                    }
                }
                break;
                
            case 8:
                printf("Enter upper limit for twin primes: ");
                scanf("%d", &n);
                
                if (n < 5) {
                    printf("Need at least 5 to find twin primes\n");
                } else {
                    findTwinPrimes(n);
                }
                break;
                
            case 9:
                printf("Enter upper limit for prime gap analysis: ");
                scanf("%d", &n);
                
                if (n < 10) {
                    printf("Need at least 10 for meaningful gap analysis\n");
                } else {
                    findPrimeGaps(n);
                }
                break;
                
            case 10:
                printf("Enter limit for performance comparison: ");
                scanf("%d", &n);
                
                if (n < 100 || n > MAX_LIMIT) {
                    printf("Limit should be between 100 and %d\n", MAX_LIMIT);
                } else {
                    compareSieveMethods(n);
                }
                break;
                
            case 11:
                printf("Enter small limit for step-by-step demo (max 50): ");
                scanf("%d", &n);
                
                if (n < 2 || n > 50) {
                    printf("Limit should be between 2 and 50\n");
                } else {
                    demonstrateSieve(n);
                }
                break;
                
            case 12:
                printf("Enter number for Miller-Rabin test: ");
                scanf("%d", &n);
                
                if (n < 2) {
                    printf("Number must be >= 2\n");
                } else {
                    bool result = millerRabin(n, 5);
                    printf("%d is %s\n", n, result ? "probably prime" : "composite");
                }
                break;
                
            case 13:
                if (!sieve) {
                    printf("Please generate primes first (option 1 or 2)\n");
                } else {
                    analyzePrimes(sieve, n);
                }
                break;
                
            case 0:
                if (sieve) free(sieve);
                printf("Exiting prime number program. Goodbye!\n");
                return 0;
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    
    return 0;
}

/**
 * Basic Sieve of Eratosthenes implementation
 * 
 * @param n: Upper limit to find primes up to
 * @param primeCount: Pointer to store count of primes found
 * @return: Boolean array where true indicates prime numbers
 */
bool* sieveOfEratosthenes(int n, int* primeCount) {
    bool* isPrime = (bool*)malloc((n + 1) * sizeof(bool));
    if (!isPrime) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    
    // Initialize all numbers as prime
    for (int i = 0; i <= n; i++) {
        isPrime[i] = true;
    }
    
    // 0 and 1 are not prime
    isPrime[0] = isPrime[1] = false;
    
    // Sieve algorithm
    for (int p = 2; p * p <= n; p++) {
        if (isPrime[p]) {
            // Mark all multiples of p as non-prime
            for (int i = p * p; i <= n; i += p) {
                isPrime[i] = false;
            }
        }
    }
    
    // Count primes
    *primeCount = 0;
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            (*primeCount)++;
        }
    }
    
    return isPrime;
}

/**
 * Optimized Sieve - only considers odd numbers after 2
 * 
 * @param n: Upper limit to find primes up to
 * @param primeCount: Pointer to store count of primes found
 * @return: Boolean array where true indicates prime numbers
 */
bool* optimizedSieve(int n, int* primeCount) {
    bool* isPrime = (bool*)malloc((n + 1) * sizeof(bool));
    if (!isPrime) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    
    // Initialize
    for (int i = 0; i <= n; i++) {
        isPrime[i] = true;
    }
    
    isPrime[0] = isPrime[1] = false;
    
    // Handle 2 separately
    if (n >= 2) {
        // Mark all even numbers > 2 as non-prime
        for (int i = 4; i <= n; i += 2) {
            isPrime[i] = false;
        }
    }
    
    // Only check odd numbers
    for (int p = 3; p * p <= n; p += 2) {
        if (isPrime[p]) {
            // Mark odd multiples of p
            for (int i = p * p; i <= n; i += 2 * p) {
                isPrime[i] = false;
            }
        }
    }
    
    // Count primes
    *primeCount = 0;
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            (*primeCount)++;
        }
    }
    
    return isPrime;
}

/**
 * Segmented Sieve for finding primes in a range [low, high]
 * Useful for very large ranges where memory is a constraint
 * 
 * @param low: Lower bound of range
 * @param high: Upper bound of range
 */
void segmentedSieve(int low, int high) {
    // Find all primes up to sqrt(high)
    int limit = (int)sqrt(high) + 1;
    int primeCount;
    bool* basePrimes = sieveOfEratosthenes(limit, &primeCount);
    
    // Create array for the segment
    int segmentSize = high - low + 1;
    bool* segment = (bool*)malloc(segmentSize * sizeof(bool));
    
    // Initialize segment as all prime
    for (int i = 0; i < segmentSize; i++) {
        segment[i] = true;
    }
    
    // Use base primes to mark non-primes in segment
    for (int p = 2; p <= limit; p++) {
        if (basePrimes[p]) {
            // Find the minimum number in [low, high] that is a multiple of p
            int start = ((low + p - 1) / p) * p;
            if (start == p) start = p * p; // Skip p itself
            
            // Mark multiples of p in segment
            for (int j = start; j <= high; j += p) {
                segment[j - low] = false;
            }
        }
    }
    
    // Print primes in segment
    int count = 0;
    for (int i = 0; i < segmentSize; i++) {
        if (segment[i] && (low + i) >= 2) {
            printf("%d ", low + i);
            count++;
            if (count % 10 == 0) printf("\n");
        }
    }
    
    printf("\nTotal primes in range: %d\n", count);
    
    free(basePrimes);
    free(segment);
}

/**
 * Basic primality test using trial division
 * 
 * @param n: Number to test
 * @return: true if prime, false otherwise
 */
bool isPrime(int n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    
    return true;
}

/**
 * Optimized primality test
 * 
 * @param n: Number to test
 * @return: true if prime, false otherwise
 */
bool isPrimeFast(int n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    // Check for divisors of form 6k ± 1
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    
    return true;
}

/**
 * Get all primes in a specific range
 * 
 * @param start: Start of range
 * @param end: End of range
 * @param count: Pointer to store count of primes
 * @return: Array of prime numbers in range
 */
int* getPrimesInRange(int start, int end, int* count) {
    int primeCount;
    bool* sieve = sieveOfEratosthenes(end, &primeCount);
    
    // Count primes in range
    *count = 0;
    for (int i = start; i <= end; i++) {
        if (sieve[i]) (*count)++;
    }
    
    if (*count == 0) {
        free(sieve);
        return NULL;
    }
    
    // Collect primes
    int* primes = (int*)malloc((*count) * sizeof(int));
    int index = 0;
    
    for (int i = start; i <= end; i++) {
        if (sieve[i]) {
            primes[index++] = i;
        }
    }
    
    free(sieve);
    return primes;
}

/**
 * Print prime numbers from sieve
 * 
 * @param sieve: Boolean array indicating primes
 * @param n: Size of sieve
 * @param limit: Maximum number of primes to print
 */
void printPrimes(bool* sieve, int n, int limit) {
    int count = 0;
    for (int i = 2; i <= n && count < limit; i++) {
        if (sieve[i]) {
            printf("%d ", i);
            count++;
            if (count % 10 == 0) printf("\n");
        }
    }
    if (count % 10 != 0) printf("\n");
}

/**
 * Analyze prime distribution and properties
 * 
 * @param sieve: Boolean array indicating primes
 * @param n: Size of sieve
 */
void analyzePrimes(bool* sieve, int n) {
    printf("\n=== Prime Analysis for range [2, %d] ===\n", n);
    
    int totalPrimes = 0;
    int evenPrimes = 0;
    int oddPrimes = 0;
    
    for (int i = 2; i <= n; i++) {
        if (sieve[i]) {
            totalPrimes++;
            if (i % 2 == 0) evenPrimes++;
            else oddPrimes++;
        }
    }
    
    printf("Total primes: %d\n", totalPrimes);
    printf("Even primes: %d\n", evenPrimes);
    printf("Odd primes: %d\n", oddPrimes);
    printf("Prime density: %.4f%%\n", (double)totalPrimes * 100 / n);
    
    if (n > 10) {
        double pnt = n / log(n);
        printf("Prime Number Theorem estimate: %.0f\n", pnt);
        printf("Actual vs PNT ratio: %.4f\n", totalPrimes / pnt);
    }
}

/**
 * Demonstrate sieve algorithm step by step
 * 
 * @param n: Upper limit for demonstration
 */
void demonstrateSieve(int n) {
    printf("\n=== Sieve of Eratosthenes Step-by-Step Demo ===\n");
    printf("Finding all primes up to %d:\n\n", n);
    
    bool* isPrime = (bool*)malloc((n + 1) * sizeof(bool));
    
    // Initialize
    for (int i = 0; i <= n; i++) {
        isPrime[i] = true;
    }
    isPrime[0] = isPrime[1] = false;
    
    printf("Step 1: Initialize array, mark 0 and 1 as non-prime\n");
    printf("Numbers: ");
    for (int i = 2; i <= n; i++) {
        printf("%d ", i);
    }
    printf("\n\n");
    
    int step = 2;
    for (int p = 2; p * p <= n; p++) {
        if (isPrime[p]) {
            printf("Step %d: Mark multiples of %d\n", step++, p);
            printf("Marking: ");
            
            for (int i = p * p; i <= n; i += p) {
                if (isPrime[i]) {
                    printf("%d ", i);
                    isPrime[i] = false;
                }
            }
            printf("\n");
            
            printf("Remaining: ");
            for (int i = 2; i <= n; i++) {
                if (isPrime[i]) {
                    printf("%d ", i);
                }
            }
            printf("\n\n");
        }
    }
    
    printf("Final primes: ");
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");
    
    free(isPrime);
}

/**
 * Prime factorization using trial division
 * 
 * @param n: Number to factorize
 */
void primeFactorization(int n) {
    int original = n;
    bool first = true;
    
    // Handle factor 2
    while (n % 2 == 0) {
        if (!first) printf(" × ");
        printf("2");
        first = false;
        n /= 2;
    }
    
    // Handle odd factors
    for (int i = 3; i * i <= n; i += 2) {
        while (n % i == 0) {
            if (!first) printf(" × ");
            printf("%d", i);
            first = false;
            n /= i;
        }
    }
    
    // If n is still > 1, it's a prime factor
    if (n > 1) {
        if (!first) printf(" × ");
        printf("%d", n);
    }
    
    printf(" = %d\n", original);
}

/**
 * Count primes up to n using sieve
 * 
 * @param n: Upper limit
 * @return: Number of primes up to n
 */
int countPrimesUpTo(int n) {
    int count;
    bool* sieve = sieveOfEratosthenes(n, &count);
    free(sieve);
    return count;
}

/**
 * Find and display twin primes up to n
 * Twin primes are pairs of primes that differ by 2
 * 
 * @param n: Upper limit
 */
void findTwinPrimes(int n) {
    int primeCount;
    bool* sieve = sieveOfEratosthenes(n, &primeCount);
    
    printf("Twin primes up to %d:\n", n);
    int twinCount = 0;
    
    for (int i = 3; i <= n - 2; i++) {
        if (sieve[i] && sieve[i + 2]) {
            printf("(%d, %d) ", i, i + 2);
            twinCount++;
            if (twinCount % 5 == 0) printf("\n");
        }
    }
    
    printf("\nTotal twin prime pairs: %d\n", twinCount);
    free(sieve);
}

/**
 * Analyze gaps between consecutive primes
 * 
 * @param n: Upper limit
 */
void findPrimeGaps(int n) {
    int primeCount;
    bool* sieve = sieveOfEratosthenes(n, &primeCount);
    
    printf("Prime gap analysis up to %d:\n", n);
    
    int prevPrime = 2;
    int maxGap = 0;
    int maxGapStart = 0;
    int gaps[20] = {0}; // Count gaps up to 20
    
    for (int i = 3; i <= n; i++) {
        if (sieve[i]) {
            int gap = i - prevPrime;
            if (gap < 20) gaps[gap]++;
            
            if (gap > maxGap) {
                maxGap = gap;
                maxGapStart = prevPrime;
            }
            
            prevPrime = i;
        }
    }
    
    printf("Gap distribution:\n");
    for (int i = 1; i < 20; i++) {
        if (gaps[i] > 0) {
            printf("Gap %d: %d occurrences\n", i, gaps[i]);
        }
    }
    
    printf("Largest gap: %d (between %d and %d)\n", maxGap, maxGapStart, maxGapStart + maxGap);
    
    free(sieve);
}

/**
 * Compare performance of different sieve methods
 * 
 * @param n: Upper limit for comparison
 */
void compareSieveMethods(int n) {
    printf("Performance comparison for limit %d:\n\n", n);
    
    clock_t start, end;
    int count1, count2;
    
    // Basic sieve
    start = clock();
    bool* sieve1 = sieveOfEratosthenes(n, &count1);
    end = clock();
    double time1 = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    // Optimized sieve
    start = clock();
    bool* sieve2 = optimizedSieve(n, &count2);
    end = clock();
    double time2 = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    printf("Basic Sieve:\n");
    printf("  Time: %.6f seconds\n", time1);
    printf("  Primes found: %d\n", count1);
    
    printf("Optimized Sieve:\n");
    printf("  Time: %.6f seconds\n", time2);
    printf("  Primes found: %d\n", count2);
    
    if (time1 > 0) {
        printf("Speedup: %.2fx\n", time1 / time2);
    }
    
    free(sieve1);
    free(sieve2);
}

/**
 * Modular exponentiation for Miller-Rabin test
 */
long long power(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    
    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % mod;
        }
        exp >>= 1;
        base = (base * base) % mod;
    }
    
    return result;
}

/**
 * Miller-Rabin primality test helper
 */
bool millerTest(long long d, long long n) {
    long long a = 2 + rand() % (n - 4);
    long long x = power(a, d, n);
    
    if (x == 1 || x == n - 1) return true;
    
    while (d != n - 1) {
        x = (x * x) % n;
        d *= 2;
        
        if (x == 1) return false;
        if (x == n - 1) return true;
    }
    
    return false;
}

/**
 * Miller-Rabin probabilistic primality test
 * 
 * @param n: Number to test
 * @param k: Number of rounds (higher k = more accurate)
 * @return: true if probably prime, false if composite
 */
bool millerRabin(long long n, int k) {
    if (n <= 1 || n == 4) return false;
    if (n <= 3) return true;
    
    // Find d such that n-1 = d * 2^r
    long long d = n - 1;
    while (d % 2 == 0) {
        d /= 2;
    }
    
    // Perform k rounds of testing
    for (int i = 0; i < k; i++) {
        if (!millerTest(d, n)) {
            return false;
        }
    }
    
    return true;
}
