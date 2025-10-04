/**
 *  matrix_chain_multiplication.cpp
 *  Implementation of the Matrix Chain Multiplication (MCM) problem.
 *
 * Description:
 * This program finds the most efficient way to multiply a chain of matrices.
 * The problem is not to perform the multiplications, but to decide the sequence
 * of parenthesizations. We use a Dynamic Programming approach, specifically the
 * Partition DP pattern.
 *
 * The state dp[i][j] represents the minimum number of scalar multiplications
 * needed to compute the product of matrices from index i to j.
 *
 * The state transition is:
 * dp[i][j] = min(dp[i][k] + dp[k+1][j] + dims[i-1]*dims[k]*dims[j])
 * for all k from i to j-1.
 *
 * Complexity Analysis:
 * - Time Complexity: O(n^3), where n is the number of matrices. Three nested loops are used.
 * - Space Complexity: O(n^2) for the DP table.
 */
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

/**
 * @brief Solves the Matrix Chain Multiplication problem using tabulation.
 * @param dims A vector where dims[i-1] and dims[i] are the dimensions of matrix i.
 * @return The minimum number of scalar multiplications.
 */
int matrixChainOrder(const vector<int>& dims) {
    // There are n-1 matrices.
    int n = dims.size() - 1;
    if (n < 2) {
        return 0; // No multiplication needed if there's 0 or 1 matrix.
    }

    // dp[i][j] = Minimum number of multiplications to compute matrix M[i]...M[j]
    // where M[i] has dimensions dims[i-1] x dims[i].
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

    // L is the chain length. It varies from 2 to n.
    for (int L = 2; L <= n; ++L) {
        // i is the starting matrix index.
        for (int i = 1; i <= n - L + 1; ++i) {
            // j is the ending matrix index.
            int j = i + L - 1;
            dp[i][j] = numeric_limits<int>::max();

            // k is the partition point.
            for (int k = i; k < j; ++k) {
                // Cost to multiply M[i]..M[k] and M[k+1]..M[j]
                // and then the final two resulting matrices.
                int cost = dp[i][k] + dp[k + 1][j] + dims[i - 1] * dims[k] * dims[j];
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                }
            }
        }
    }
    return dp[1][n];
}

// Example usage and test cases
int main() {
    // Example: We have 4 matrices with dimensions:
    // M1: 10x30, M2: 30x5, M3: 5x60, M4: 60x20
    // The dimensions array will be {10, 30, 5, 60, 20}
    vector<int> dims = {10, 30, 5, 60, 20};
    cout << "The dimensions of the matrices are: ";
    for(size_t i = 0; i < dims.size() -1; ++i) {
        cout << dims[i] << "x" << dims[i+1] << (i == dims.size() - 2 ? "" : ", ");
    }
    cout << endl;

    int min_multiplications = matrixChainOrder(dims);
    cout << "Minimum number of scalar multiplications needed is: " << min_multiplications << endl; // Expected: 13500

    vector<int> dims2 = {40, 20, 30, 10, 30};
    cout << "\nFor dimensions {40, 20, 30, 10, 30}:" << endl;
    cout << "Minimum number of scalar multiplications needed is: " << matrixChainOrder(dims2) << endl; // Expected: 26000

    return 0;
}