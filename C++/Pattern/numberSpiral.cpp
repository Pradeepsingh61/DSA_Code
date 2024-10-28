#include <iostream>
#include <vector>

using namespace std;

void generateSpiralMatrix(int n) {
    // Create a 2D vector initialized with zeros
    vector<vector<int>> spiral(n, vector<int>(n, 0));
    int left = 0, right = n - 1;
    int top = 0, bottom = n - 1;
    int num = 1;
    while (left <= right && top <= bottom) {
        // Fill the top row
        for (int i = left; i <= right; ++i) {
            spiral[top][i] = num++;
        }
        top++;
        // Fill the right column
        for (int i = top; i <= bottom; ++i) {
            spiral[i][right] = num++;
        }
        right--;

        // Fill the bottom row
        if (top <= bottom) {
            for (int i = right; i >= left; --i) {
                spiral[bottom][i] = num++;
            }
            bottom--;
        }

        // Fill the left column
        if (left <= right) {
            for (int i = bottom; i >= top; --i) {
                spiral[i][left] = num++;
            }
            left++;
        }
    }
    // Print the spiral matrix
    for (const auto& row : spiral) {
        for (int val : row) {
            cout << val << "\t"; // Use tab for better alignment
        }
        cout << endl;
    }
}

int main() {
    int n;
    cout << "Enter the size of the spiral matrix (n x n): ";
    cin >> n;
    generateSpiralMatrix(n);
    return 0;
}