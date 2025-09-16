"""
Karatsuba Algorithm for Multiplying Large Numbers

Problem Statement:
The challenge of multiplying large numbers efficiently is crucial in computer science and numerical computations. 
Traditional multiplication methods have a time complexity of O(n^2), where n is the number of digits in the numbers being multiplied. 
As the size of the numbers increases, the time taken to perform multiplication grows quadratically.

Theory:
The Karatsuba algorithm, developed by Anatolii Alexeevitch Karatsuba, is a divide-and-conquer algorithm that reduces the 
multiplication of two n-digit numbers to at most three multiplications of n/2-digit numbers, 
along with some additional additions and shifts. This method reduces the time complexity to approximately O(n^(log2 3)) ≈ O(n^1.585), 
making it significantly faster for large numbers.

The algorithm involves the following steps:
1. Split each number into two halves.
2. Recursively compute three products:
   - ac (product of the most significant parts)
   - bd (product of the least significant parts)
   - (a + b)(c + d)
3. Combine the results to get the final product.

"""

def karatsuba(x, y):
    # Base case for recursion
    if x < 10 or y < 10:
        return x * y

    # Calculate the size of the numbers
    max_len = max(len(str(x)), len(str(y)))
    half_len = max_len // 2

    # Split the digit sequences in the middle
    a = x // (10 ** half_len)  # Most significant digits
    b = x % (10 ** half_len)   # Least significant digits
    c = y // (10 ** half_len)  # Most significant digits
    d = y % (10 ** half_len)    # Least significant digits

    # 3 recursive calls to compute the products
    ac = karatsuba(a, c)       # a * c
    bd = karatsuba(b, d)       # b * d
    abcd = karatsuba(a + b, c + d)  # (a + b) * (c + d)

    # Use the results to get the final product
    return (ac * 10 ** (2 * half_len)) + \
           ((abcd - ac - bd) * 10 ** half_len) + \
           bd

# Taking user input
x = int(input("Enter the first number: "))
y = int(input("Enter the second number: "))

# Calculating the product using the Karatsuba algorithm
result = karatsuba(x, y)

# Displaying the result
print(f"The product of {x} and {y} is: {result}")
