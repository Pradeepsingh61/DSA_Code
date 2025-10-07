#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to implement Sieve of Eratosthenes
void sieveOfEratosthenes(int n) {
    // Create a boolean array "prime[0..n]" and initialize
    // all entries as true. A value in prime[i] will
    // finally be false if i is Not a prime, else true.
    int *prime = (int *)malloc((n + 1) * sizeof(int));
    
    for (int i = 0; i <= n; i++)
        prime[i] = 1;
 
    for (int p = 2; p * p <= n; p++) {
        // If prime[p] is not changed, then it is a prime
        if (prime[p] == 1) {
            // Update all multiples of p greater than or equal to p^2
            for (int i = p * p; i <= n; i += p)
                prime[i] = 0;
        }
    }
 
    // Print all prime numbers
    printf("Prime numbers up to %d:\n", n);
    for (int p = 2; p <= n; p++)
        if (prime[p])
            printf("%d ", p);
    printf("\n");
    
    free(prime);
}

// Function to implement Segmented Sieve
void segmentedSieve(int n) {
    // Compute all primes smaller than or equal to square root of n using simple sieve
    int limit = (int)sqrt(n) + 1;
    
    // Create and initialize the base primes array
    int *basePrimes = (int *)malloc(limit * sizeof(int));
    int count = 0;
    
    // Use simple sieve to find all primes up to sqrt(n)
    int *mark = (int *)calloc(limit + 1, sizeof(int));
    
    for (int p = 2; p * p < limit; p++) {
        if (mark[p] == 0) {
            for (int i = p * p; i < limit; i += p)
                mark[i] = 1;
        }
    }
    
    // Store the base primes
    for (int p = 2; p < limit; p++) {
        if (mark[p] == 0) {
            basePrimes[count] = p;
            count++;
        }
    }
    
    // Now use the base primes to find primes in the range [limit, n]
    int low = limit;
    int high = 2 * limit;
    
    printf("Prime numbers up to %d using segmented sieve:\n", n);
    
    // Print primes found by simple sieve
    for (int i = 0; i < count; i++)
        printf("%d ", basePrimes[i]);
    
    // Process segments one by one
    while (low < n) {
        if (high > n)
            high = n;
            
        int *mark = (int *)calloc(limit + 1, sizeof(int));
        
        // Mark multiples of base primes in the current range
        for (int i = 0; i < count; i++) {
            int p = basePrimes[i];
            
            // Find the minimum number in [low..high] that is a multiple of p
            int lowLim = (low / p) * p;
            if (lowLim < low)
                lowLim += p;
                
            for (int j = lowLim; j < high; j += p)
                mark[j - low] = 1;
        }
        
        // Print numbers not marked in current range
        for (int i = low; i < high; i++)
            if (mark[i - low] == 0 && i > 1)
                printf("%d ", i);
                
        // Update low and high for next segment
        low += limit;
        high += limit;
        free(mark);
    }
    
    printf("\n");
    free(basePrimes);
    free(mark);
}

// Function to analyze prime distribution
void analyzePrimes(int n) {
    printf("Analyzing prime distribution up to %d:\n", n);
    
    // Count primes up to n using the prime number theorem approximation
    // π(n) ~ n / ln(n)
    double primeCount = n / log(n);
    printf("Approximate number of primes up to %d: %.0f\n", n, primeCount);
    
    // Goldbach's conjecture: Every even integer greater than 2 can be expressed 
    // as the sum of two primes
    printf("Goldbach's conjecture verification (even numbers 4-20):\n");
    
    // Simple implementation to verify Goldbach's conjecture for small numbers
    for (int num = 4; num <= 20; num += 2) {
        int found = 0;
        for (int i = 2; i <= num / 2; i++) {
            // Simple primality check for demonstration
            int isPrime = 1;
            for (int j = 2; j * j <= i; j++) {
                if (i % j == 0) {
                    isPrime = 0;
                    break;
                }
            }
            if (isPrime) {
                int other = num - i;
                isPrime = 1;
                for (int j = 2; j * j <= other; j++) {
                    if (other % j == 0) {
                        isPrime = 0;
                        break;
                    }
                }
                if (isPrime && other > 1) {
                    printf("%d = %d + %d\n", num, i, other);
                    found = 1;
                    break;
                }
            }
        }
        if (!found) {
            printf("Goldbach's conjecture fails for %d!\n", num);
        }
    }
}

int main() {
    int n;
    printf("Enter a number to find all primes up to that number: ");
    scanf("%d", &n);
    
    if (n < 2) {
        printf("There are no prime numbers less than 2.\n");
        return 0;
    }
    
    // Simple Sieve of Eratosthenes
    sieveOfEratosthenes(n);
    
    // Segmented Sieve (more efficient for large n)
    if (n > 100) {
        printf("\nUsing segmented sieve for better performance...\n");
        segmentedSieve(n);
    }
    
    // Analyze prime distribution
    if (n >= 10) {
        analyzePrimes(n);
    }
    
    return 0;
}
