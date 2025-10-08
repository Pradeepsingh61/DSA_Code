# 📌 Euclidean Algorithm for Greatest Common Divisor (GCD)

"""
Algorithm: Euclidean Algorithm
Description: Computes the greatest common divisor (GCD) of two non-negative integers.
Time Complexity: O(log(min(a, b))) - The number of steps is proportional to the number of digits in the smaller number.
Space Complexity: O(log(min(a, b))) for recursive calls, O(1) for iterative.
Author: Gemini
"""

def gcd_recursive(a: int, b: int) -> int:
    """
    Computes the greatest common divisor (GCD) of two non-negative integers using the recursive Euclidean algorithm.

    Args:
        a (int): The first non-negative integer.
        b (int): The second non-negative integer.

    Returns:
        int: The greatest common divisor of a and b.

    Raises:
        ValueError: If either a or b is negative.
    """
    if a < 0 or b < 0:
        raise ValueError("Both numbers must be non-negative.")
    if b == 0:
        return a
    return gcd_recursive(b, a % b)

def gcd_iterative(a: int, b: int) -> int:
    """
    Computes the greatest common divisor (GCD) of two non-negative integers using the iterative Euclidean algorithm.

    Args:
        a (int): The first non-negative integer.
        b (int): The second non-negative integer.

    Returns:
        int: The greatest common divisor of a and b.

    Raises:
        ValueError: If either a or b is negative.
    """
    if a < 0 or b < 0:
        raise ValueError("Both numbers must be non-negative.")
    while b:
        a, b = b, a % b
    return a

def main():
    """Test the Euclidean algorithm with example cases."""
    test_cases = [
        (48, 18, 6),
        (101, 103, 1),
        (0, 5, 5),
        (7, 0, 7),
        (10, 10, 10),
        (1, 1, 1),
        (12, 15, 3),
        (270, 192, 6)
    ]

    print("--- Recursive GCD ---")
    for a, b, expected in test_cases:
        try:
            result = gcd_recursive(a, b)
            print(f"GCD_recursive({a}, {b}) = {result} (Expected: {expected}) {'✅' if result == expected else '❌'}")
        except ValueError as e:
            print(f"GCD_recursive({a}, {b}) raised error: {e} (Expected: {expected}) ❌")

    print("\n--- Iterative GCD ---")
    for a, b, expected in test_cases:
        try:
            result = gcd_iterative(a, b)
            print(f"GCD_iterative({a}, {b}) = {result} (Expected: {expected}) {'✅' if result == expected else '❌'}")
        except ValueError as e:
            print(f"GCD_iterative({a}, {b}) raised error: {e} (Expected: {expected}) ❌")

    # Test edge cases with negative numbers
    print("\n--- Negative Number Test Cases ---")
    negative_test_cases = [
        (-5, 10),
        (10, -5),
        (-5, -10)
    ]
    for a, b in negative_test_cases:
        try:
            gcd_recursive(a, b)
            print(f"GCD_recursive({a}, {b}) - Expected ValueError, but no error. ❌")
        except ValueError as e:
            print(f"GCD_recursive({a}, {b}) - Caught expected error: {e} ✅")
        try:
            gcd_iterative(a, b)
            print(f"GCD_iterative({a}, {b}) - Expected ValueError, but no error. ❌")
        except ValueError as e:
            print(f"GCD_iterative({a}, {b}) - Caught expected error: {e} ✅")


if __name__ == "__main__":
    main()