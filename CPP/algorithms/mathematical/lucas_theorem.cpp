/*
 * Lucas' Theorem for Computing Binomial Coefficients Modulo Prime
 * 
 * This algorithm efficiently computes the binomial coefficient C(n,k) % p
 * for large values of n and k, where p is a small prime number.
 *
 * Time Complexity: O(p^2 + log n)
 * - p^2 for precomputing small binomial coefficients
 * - log n for the number of digits in base p
 * 
 * Author: GitHub Copilot
 * Date: October 2, 2025
 */

#include <iostream>
#include <vector>
using namespace std;

class LucasTheorem {
private:
    // Precompute binomial coefficients for small values (0 to p-1)
    vector<vector<int>> precompute_binomial(int p) {
        // Create a 2D vector to store C(i,j) for i,j from 0 to p-1
        vector<vector<int>> C(p, vector<int>(p, 0));
        
        // Base cases
        for (int i = 0; i < p; i++) {
            C[i][0] = 1; // C(n,0) = 1
        }
        
        // Calculate using the recursive formula: C(n,k) = C(n-1,k-1) + C(n-1,k)
        for (int i = 1; i < p; i++) {
            for (int j = 1; j <= i; j++) {
                C[i][j] = (C[i-1][j-1] + C[i-1][j]) % p;
            }
        }
        
        return C;
    }
    
public:
    // Calculate C(n,k) mod p using Lucas' Theorem
    int nCk_mod_p(long long n, long long k, int p) {
        // Precompute binomial coefficients for small values
        vector<vector<int>> C = precompute_binomial(p);
        
        // Base cases
        if (k < 0 || k > n) return 0;
        if (k == 0 || k == n) return 1;
        
        // Initialize result
        int result = 1;
        
        // Apply Lucas' Theorem
        // We compute the base p representation of n and k
        // and use the formula: C(n,k) % p = ∏ C(n_i,k_i) % p
        while (n > 0 || k > 0) {
            // Extract last digit in base p
            int n_i = n % p;
            int k_i = k % p;
            
            // If k_i > n_i, the binomial coefficient is 0
            if (k_i > n_i) {
                return 0;
            }
            
            // Multiply with the precomputed value
            result = (result * C[n_i][k_i]) % p;
            
            // Move to the next digits
            n /= p;
            k /= p;
        }
        
        return result;
    }
};

int main() {
    LucasTheorem lucas;
    
    // Example 1: Small values
    int n1 = 10, k1 = 5, p1 = 7;
    cout << "Example 1: C(" << n1 << ", " << k1 << ") mod " << p1 << " = " 
         << lucas.nCk_mod_p(n1, k1, p1) << endl;
    
    // Example 2: Large values
    long long n2 = 1000000000LL, k2 = 500000000LL, p2 = 13;
    cout << "Example 2: C(" << n2 << ", " << k2 << ") mod " << p2 << " = " 
         << lucas.nCk_mod_p(n2, k2, p2) << endl;
    
    // Example 3: Another test case
    long long n3 = 123456789LL, k3 = 987654LL, p3 = 29;
    cout << "Example 3: C(" << n3 << ", " << k3 << ") mod " << p3 << " = " 
         << lucas.nCk_mod_p(n3, k3, p3) << endl;
    
    // Example 4: Edge case where k > n
    long long n4 = 10, k4 = 20, p4 = 7;
    cout << "Example 4: C(" << n4 << ", " << k4 << ") mod " << p4 << " = " 
         << lucas.nCk_mod_p(n4, k4, p4) << endl;
    
    return 0;
}
