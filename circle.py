"""
Circle Properties Calculation

Description:
This algorithm calculates the area and circumference of a circle given its radius.
It uses the formulas:
    Area = π * r^2
    Circumference = 2 * π * r

Approach:
- Take the radius as input
- Compute area and circumference
- Return both values

Use Cases:
- Geometry calculations
- Basic math learning
- DSA practice examples

Time Complexity: O(1)
- All calculations are done in constant time, independent of input size.

Space Complexity: O(1)
- Uses only a few variables, no extra data structures needed.
"""

import math  # Import math module to access pi

def circle_properties(radius):
    """
    Calculates area and circumference of a circle given its radius
    :param radius: Radius of the circle
    :return: Tuple (area, circumference) or error message for negative radius
    """
    # Validate input
    if radius < 0:
        return "Error: Radius cannot be negative"

    # Calculate area using formula π * r^2
    area = math.pi * radius * radius
    
    # Calculate circumference using formula 2 * π * r
    circumference = 2 * math.pi * radius
    
    # Return both results
    return area, circumference

# Example usage / Test cases
if __name__ == "__main__":
    test_radii = [5, 0, -3]  # Different test cases including edge cases

    for r in test_radii:
        result = circle_properties(r)
        print(f"Radius: {r}")
        print(f"Result: {result}")
        print("-" * 30)
