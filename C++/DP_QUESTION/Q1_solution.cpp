class Solution {
public:

// Function to calculate the largest rectangle area in a histogram
int largestRectangleArea(vector<int> &A) {
    
    stack<int> st, st1;  // Two stacks to store indices of the heights
    int n = A.size();
    
    // Vector to store the index of the left boundary for each bar
    vector<int> left(A.size(), 0);
    
    // Calculate the left boundary for each bar
    for (int i = 0; i < n; i++) {
        // Pop elements from the stack until we find a bar smaller than the current one
        while (!st.empty() && A[st.top()] >= A[i]) {
            st.pop();
        }
        // If stack is empty, it means there is no smaller element to the left
        if (st.empty()) 
            left[i] = 0;
        else
            // Otherwise, the left boundary is one index after the top of the stack
            left[i] = st.top() + 1;
        
        // Push the current index onto the stack
        st.push(i);
    }
    
    // Vector to store the index of the right boundary for each bar
    vector<int> right(A.size(), 0);
    
    // Calculate the right boundary for each bar
    for (int i = n - 1; i >= 0; i--) {
        // Pop elements from the stack until we find a bar smaller than the current one
        while (!st1.empty() && A[st1.top()] >= A[i]) {
            st1.pop();
        }
        // If stack is empty, it means there is no smaller element to the right
        if (st1.empty())
            right[i] = n - 1;
        else
            // Otherwise, the right boundary is one index before the top of the stack
            right[i] = st1.top() - 1;
        
        // Push the current index onto the stack
        st1.push(i);
    }
    
    int mx = -1;  // Variable to store the maximum area found
    
    // Calculate the area for each bar and update the maximum area
    for (int i = 0; i < left.size(); i++) {
        // Area = height * width (where width is right[i] - left[i] + 1)
        mx = max((right[i] - left[i] + 1) * A[i], mx);
    }
    
    return mx;  // Return the maximum rectangle area
}

// Function to calculate the maximal rectangle area in a binary matrix
int maximalRectangle(vector<vector<char>>& matrix) {
    int n = matrix.size();    // Number of rows in the matrix
    int m = matrix[0].size(); // Number of columns in the matrix
    
    // Create a matrix to store the heights of histograms
    vector<vector<int>> matrix1(n, vector<int>(m, 0));
    
    // Convert the binary matrix into a histogram representation
    for (int j = 0; j < m; j++) {
        int sum = 0;  // Variable to accumulate the height of consecutive '1's
        for (int i = 0; i < n; i++) {
            if (matrix[i][j] == '1') {
                sum++;  // Increment height if '1' is found
                matrix1[i][j] = sum;  // Store the height
            } else {
                sum = 0;  // Reset the height if '0' is found
                matrix1[i][j] = sum;
            }
        }
    }

    int mx = 0;  // Variable to store the maximal rectangle area

    // For each row in the matrix1 (histogram heights), calculate the largest rectangle
    for (auto i : matrix1) {
        vector<int> v1 = i;  // Extract the row as a histogram
        mx = max(mx, largestRectangleArea(v1));  // Calculate the largest rectangle in this histogram
    }
    
    return mx;  // Return the maximal rectangle area
}
};
