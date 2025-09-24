#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
// Function to calculate the largest rectangle area in a histogram
int largestRectangleArea(std::vector<int>& heights) {
    std::stack<int> st;
    int maxArea = 0;
    int n = heights.size();

    for (int i = 0; i < n; i++) {
        while (!st.empty() && heights[st.top()] >= heights[i]) {
            int height = heights[st.top()];
            st.pop();
            int width = st.empty() ? i : i - st.top() - 1;
            maxArea = std::max(maxArea, height * width);
        }
        st.push(i);
    }

    // Final pass to process remaining indices in the stack
    while (!st.empty()) {
        int height = heights[st.top()];
        st.pop();
        int width = st.empty() ? n : n - st.top() - 1;
        maxArea = std::max(maxArea, height * width);
    }

    return maxArea;
}

// Function to find the maximum rectangle area in a binary matrix
int maxRectangle(std::vector<std::vector<int>>& mat) {
    if (mat.empty()) return 0;

    int maxArea = 0;
    int rows = mat.size();
    int cols = mat[0].size();
    std::vector<int> heights(cols, 0);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            heights[j] = mat[i][j] == 0 ? 0 : heights[j] + 1;
        }
        maxArea = std::max(maxArea, largestRectangleArea(heights));
    }

    return maxArea;
}

int main() {
    std::vector<std::vector<int>> mat = {
        {1, 0, 1, 0, 0},
        {1, 0, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 0, 0, 1, 0}
    };

    std::cout << "Maximum rectangle area: " << maxRectangle(mat) << std::endl;

    return 0;
}

/*
 * Algorithm Explanation:
 * - largestRectangleArea function computes the largest rectangular area in a histogram using a stack.
 *   For each bar, it finds the largest rectangle that can be formed with that bar as the shortest.
 * 
 * - maxRectangle function finds the largest rectangle in a binary matrix. It converts each row into
 *   a histogram of heights and calculates the maximum rectangle area by calling largestRectangleArea.
 *
 * Time Complexity:
 * - largestRectangleArea: O(n), where n is the number of columns.
 * - maxRectangle: O(rows * cols), where rows and cols are the dimensions of the matrix.
 *
 * Space Complexity:
 * - largestRectangleArea: O(cols) for the stack used to store indices.
 * - maxRectangle: O(cols) for the heights array.
 * - Overall auxiliary space: O(cols) + O(cols) = O(cols).
 */
