/*
Problem: Number Spiral (CSES Problem Set)
Link: https://cses.fi/problemset/task/1071/
Topic: Math / Pattern Recognition

Description:
Given coordinates (y, x) in an infinite number spiral, find the value at that position.
The spiral grows outwards starting from 1 at (1,1).

Example spiral pattern:
  1   2   9  10 25
  4   3   8  11 24
  5   6   7  12 23
 16  15  14  13 22
 17  18  19  20 21

Approach:
- The maximum of (x, y) determines which square layer the cell belongs to.
- The last number of each layer (n) is always n^2.
- Depending on whether n is even or odd, the numbering direction differs:
  - Even layers fill top-to-bottom.
  - Odd layers fill left-to-right.
- Use this pattern to directly calculate the value at (x, y) in O(1) time.

Time Complexity: O(1)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

long long numberSpiralValue(long long x, long long y) {
    if (x == 1 && y == 1) return 1;

    long long layer = max(x, y);
    long long base = (layer - 1) * (layer - 1);

    if (layer % 2 == 0) {  // even layer
        if (y == layer) 
            return base + x;
        else 
            return base + layer + (layer - y);
    } 
    else {  // odd layer
        if (x == layer)
            return base + y;
        else
            return base + layer + (layer - x);
    }
}

int main() {
    vector<pair<long long, long long>> tests = {
        {2, 3}, // Expected output: 8
        {1, 1}, // Expected output: 1
        {4, 2}, // Expected output: 15
        {3, 5}  // Expected output: 27
    };

    for (auto [y, x] : tests) {
        cout << "Input (y=" << y << ", x=" << x << ") -> Output: " 
             << numberSpiralValue(x, y) << endl;
    }

    return 0;
}
