/*
Number Spiral (CSES Problem 1071)
Language: C++
Problem Description:
You are given coordinates (y, x) in an infinite grid that forms a "number spiral".
The spiral starts at (1, 1) = 1 and moves right and upward in square layers.

Your task: For each pair (y, x), determine the number located at that cell.

Example (small spiral visualization):

    1   2   9  10  25
    4   3   8  11  24
    5   6   7  12  23
    16 15  14  13  22
    17 18  19  20  21

So, for coordinate (y=2, x=3), the answer is 8.

Algorithm:
1. Each layer corresponds to the maximum of x and y.
2. The square of (layer - 1) gives the value before the current layer starts.
3. Depending on whether the layer number is even or odd:
   - Even layer → spiral moves upward.
   - Odd layer  → spiral moves rightward.
4. Using conditional formulas, compute the number directly in O(1).

Time Complexity: O(1)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

/*
solve(x, y)
Computes the value at coordinates (y, x) in the number spiral.

Parameters:
x -> Column index (1-based)
y -> Row index (1-based)

Returns:
The number located at position (y, x)
*/
long long solve(long long x, long long y) {
    if (x == 1LL && y == 1LL) return 1LL;

    // Layer = max(x, y)
    long long layer = max(x, y) - 1LL;
    long long baseValue = layer * layer; // Value before this layer starts

    // Even layer → starts bottom-right, moves upward
    // Odd layer  → starts top-left, moves rightward
    if (layer % 2LL == 0LL) {
        if (y == layer + 1LL)
            return baseValue + x;                  // On bottom row of even layer
        else
            return baseValue + x + layer + 1LL - y; // Moving upward
    } else {
        if (x == layer + 1LL)
            return baseValue + y;                  // On right column of odd layer
        else
            return baseValue + y + layer + 1LL - x; // Moving leftward
    }
}

int main() {
    
    // Example test cases for verification
    cout << "Example Test Cases:" << endl;

    cout << "Test 1 -> y=2, x=3 | Expected: 8 | Got: " << solve(3, 2) << endl;
    cout << "Test 2 -> y=1, x=1 | Expected: 1 | Got: " << solve(1, 1) << endl;
    cout << "Test 3 -> y=4, x=2 | Expected: 15 | Got: " << solve(2, 4) << endl;
    cout << "Test 4 -> y=5, x=5 | Expected: 21 | Got: " << solve(5, 5) << endl;

    return 0;
}

/*
Expected Output:
Example Test Cases:
Test 1 -> y=2, x=3 | Expected: 8 | Got: 8
Test 2 -> y=1, x=1 | Expected: 1 | Got: 1
Test 3 -> y=4, x=2 | Expected: 15 | Got: 15
Test 4 -> y=5, x=5 | Expected: 21 | Got: 21
*/
