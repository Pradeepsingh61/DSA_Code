'''
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

'''

# Iterative Fast Exponentiation (Better Space Complexity)

def power_iterative(a, b):
    result = 1
    base = a
    
    while b > 0:
        if b % 2 == 1:   # If b is odd
            result *= base
        base *= base     # Square the base
        b //= 2          # Divide exponent by 2
    return result


# Example
print(power_iterative(2, 10))  # 1024
print(power_iterative(3, 13))  # 1594323

'''
Time Complexity: O(log b)

Space Complexity: O(1)
'''

'''
Output
1024
1594323
'''