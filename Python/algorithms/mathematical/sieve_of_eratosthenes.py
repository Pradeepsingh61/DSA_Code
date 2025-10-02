"""
Sieve of Eratosthenes for Generating Prime Numbers

Problem Statement:
Finding all prime numbers up to a given limit is a classic problem in computer science and number theory. 
The naive approach of checking each number for primality individually has a time complexity of O(n√n), 
which becomes inefficient for large limits.

Theory:
The Sieve of Eratosthenes, attributed to the ancient Greek mathematician Eratosthenes, is an efficient 
algorithm to find all primes up to a given number n. 
It works by iteratively marking the multiples of each prime starting from 2 as non-prime. 
Optimizations, such as skipping even numbers and starting marking from i*i, reduce memory usage and runtime.

Algorithm Steps:
1. Initialize a boolean array `sieve` where each index represents a number and False indicates a potential prime.
2. Explicitly include 2 as the only even prime.
3. Iterate through odd numbers starting from 3 up to sqrt(max):
   - If the number is unmarked, it is prime.
   - Mark all odd multiples of this number starting from i*i as non-prime.
4. After marking, collect all unmarked numbers (primes) including 2.

Advantages:
- Time complexity is O(n log log n), efficient for large n.
- Memory usage can be reduced by ignoring even numbers.
- Simple and elegant algorithm with clear implementation.

Use Cases:
- Cryptography
- Number theory computations
- Generating prime numbers for algorithmic problems
"""

def sieve_of_eratosthenes(max_limit):

    if max_limit < 2:
        return []

    # Initialize the sieve with False values
    sieve = [False] * (max_limit + 1)
    # include only 2 -> only even prime number
    primes = [2]

    # iterate -> only odd number, start from three
    for i in range(3, int(pow(max_limit , 0.5)+1),2):
        if not sieve[i]:

            # Mark odd multiples of i starting from i*i
            for j in range(pow(i,2),max_limit+1,2*i):
                sieve[j] = True

    
    # Collect all remaining odd primes
    for k in range(3, max_limit + 1, 2):
        if not sieve[k]:
            primes.append(k)
    
    return primes


# user input 
max_limit = int(input("Enter the limit : "))
prime_numbers = sieve_of_eratosthenes(max_limit)
print(f"Prime numbers are -> {prime_numbers}")


