# 📌 Euclidean Algorithm for Greatest Common Divisor (GCD)

"""
Algorithm: Euclidean Algorithm
Description: Computes the greatest common divisor (GCD) of two non-negative integers.
Time Complexity: O(log(min(a, b))) - The number of steps is proportional to the number of digits in the smaller number.
Space Complexity: O(log(min(a, b))) for recursive calls, O(1) for iterative.
Author: Gemini
"""

def euclidean_algorithm_recursive(a, b):
    """
    Calculates the Greatest Common Divisor (GCD) of two non-negative integers using the Euclidean algorithm recursively.

    The Euclidean algorithm is based on the principle that the greatest common divisor of two
    numbers does not change if the larger number is replaced by its difference with the smaller number.
    This process is repeated until one of the numbers becomes zero, and the other number is the GCD.

    Time Complexity: O(log(min(a, b))) - The number of steps is proportional to the number of digits in the smaller number.
    Space Complexity: O(log(min(a, b))) - Due to recursive call stack.

    Args:
        a (int): The first non-negative integer.
        b (int): The second non-negative integer.

    Returns:
        int: The Greatest Common Divisor (GCD) of a and b.

    Raises:
        ValueError: If either a or b is negative.
    """
    if a < 0 or b < 0:
        raise ValueError("Inputs must be non-negative integers.")
    # Base case: if b is 0, then a is the GCD
    if b == 0:
        return a
    # Recursive step: GCD(a, b) = GCD(b, a % b)
    return euclidean_algorithm_recursive(b, a % b)

def euclidean_algorithm_iterative(a, b):
    """
    Calculates the Greatest Common Divisor (GCD) of two non-negative integers using the Euclidean algorithm iteratively.

    Time Complexity: O(log(min(a, b))) - The number of steps is proportional to the number of digits in the smaller number.
    Space Complexity: O(1) - Uses a constant amount of extra space.

    Args:
        a (int): The first non-negative integer.
        b (int): The second non-negative integer.

    Returns:
        int: The Greatest Common Divisor (GCD) of a and b.

    Raises:
        ValueError: If either a or b is negative.
    """
    if a < 0 or b < 0:
        raise ValueError("Inputs must be non-negative integers.")
    # Loop until b becomes 0
    while b:
        # Update a and b: a becomes b, and b becomes a % b
        a, b = b, a % b
    # When b is 0, a holds the GCD
    return a

if __name__ == "__main__":
    print("Euclidean Algorithm (GCD) Tests:")

    # Test cases for recursive version
    print("\nRecursive Version:")
    test_cases = [
        (48, 18, 6),  # Standard case
        (101, 103, 1), # Prime numbers
        (0, 5, 5),    # One number is zero
        (7, 0, 7),    # One number is zero
        (10, 10, 10), # Same numbers
        (12, 4, 4),   # Divisible numbers
        (17, 23, 1)   # Co-prime numbers
    ]

    for a, b, expected in test_cases:
        try:
            result = euclidean_algorithm_recursive(a, b)
            print(f"GCD_recursive({a}, {b}) = {result} (Expected: {expected})")
            assert result == expected
        except ValueError as e:
            print(f"Error for ({a}, {b}): {e}")

    # Test cases for iterative version
    print("\nIterative Version:")
    for a, b, expected in test_cases:
        try:
            result = euclidean_algorithm_iterative(a, b)
            print(f"GCD_iterative({a}, {b}) = {result} (Expected: {expected})")
            assert result == expected
        except ValueError as e:
            print(f"Error for ({a}, {b}): {e}")

    # Test cases for negative inputs (should raise ValueError)
    print("\nNegative Input Tests:")
    negative_test_cases = [
        (-4, 2),
        (4, -2),
        (-4, -2)
    ]

    for a, b in negative_test_cases:
        try:
            euclidean_algorithm_recursive(a, b)
            print(f"GCD_recursive({a}, {b}) - Expected ValueError, but got result.")
        except ValueError as e:
            print(f"GCD_recursive({a}, {b}) - Caught expected error: {e}")

        try:
            euclidean_algorithm_iterative(a, b)
            print(f"GCD_iterative({a}, {b}) - Expected ValueError, but got result.")
        except ValueError as e:
            print(f"GCD_iterative({a}, {b}) - Caught expected error: {e}")