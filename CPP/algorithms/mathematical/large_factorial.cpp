/*
 * Large Factorial Calculation Algorithm
 * 
 * Description:
 * This algorithm calculates factorials of large numbers that exceed the range of
 * standard integer data types. The factorial of n (denoted as n!) is the product
 * of all positive integers less than or equal to n.
 * 
 * Since factorials grow extremely quickly (e.g., 20! already exceeds the range of a 64-bit integer),
 * we need special techniques to handle them:
 * 
 * 1. Store the result as an array of digits
 * 2. Perform multiplication digit by digit (similar to how we multiply numbers by hand)
 * 3. Handle carry operations properly
 * 
 * This implementation can calculate factorials of very large numbers (100+ digits).
 * 
 * Time Complexity: O(n²) where n is the input number
 * Space Complexity: O(n log n) to store the result (approximately the number of digits in n!)
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Function to calculate factorial of a large number
// Returns the result as a string
string largeFactorial(int n) {
    // Base cases
    if (n < 0) {
        return "Error: Factorial not defined for negative numbers";
    }
    if (n <= 1) {
        return "1";
    }
    
    // Initialize result as 1
    vector<int> result = {1};
    
    // Calculate n!
    for (int i = 2; i <= n; i++) {
        // Multiply current number with the result so far
        int carry = 0;
        
        // Multiply each digit and add carry
        for (size_t j = 0; j < result.size(); j++) {
            int product = result[j] * i + carry;
            result[j] = product % 10;  // Store the last digit
            carry = product / 10;      // Carry the remaining digits
        }
        
        // Add remaining carry to the result
        while (carry > 0) {
            result.push_back(carry % 10);
            carry /= 10;
        }
    }
    
    // Convert the result to a string (reverse since we stored digits from right to left)
    string factorial;
    for (auto it = result.rbegin(); it != result.rend(); ++it) {
        factorial += to_string(*it);
    }
    
    return factorial;
}

// Function to format large numbers with commas for readability
string formatWithCommas(const string& number) {
    string result = number;
    int insertPosition = result.length() - 3;
    
    while (insertPosition > 0) {
        result.insert(insertPosition, ",");
        insertPosition -= 3;
    }
    
    return result;
}

// Function to calculate factorial using standard types (for comparison)
// Note: This will overflow for n > 20 on most systems
unsigned long long standardFactorial(int n) {
    if (n <= 1) return 1;
    
    unsigned long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    
    return result;
}

// Main function with test cases
int main() {
    // Test Case 1: Small factorials (comparable with standard calculation)
    cout << "Test Case 1: Small factorials" << endl;
    for (int i = 0; i <= 10; i++) {
        cout << i << "! = " << largeFactorial(i);
        cout << " (Standard calculation: " << standardFactorial(i) << ")" << endl;
    }
    cout << endl;
    
    // Test Case 2: Medium factorials (beyond int but within unsigned long long)
    cout << "Test Case 2: Medium factorials" << endl;
    for (int i = 15; i <= 20; i++) {
        cout << i << "! = " << formatWithCommas(largeFactorial(i)) << endl;
    }
    cout << endl;
    
    // Test Case 3: Large factorials (beyond standard types)
    cout << "Test Case 3: Large factorials" << endl;
    int largeNumbers[] = {25, 50, 75, 100};
    for (int n : largeNumbers) {
        string result = largeFactorial(n);
        cout << n << "! has " << result.length() << " digits" << endl;
        cout << "First 10 digits: " << result.substr(0, 10) << "..." << endl;
        cout << "Last 10 digits: ..." << result.substr(result.length() - 10) << endl;
        cout << endl;
    }
    
    // Test Case 4: Edge cases
    cout << "Test Case 4: Edge cases" << endl;
    cout << "0! = " << largeFactorial(0) << endl;
    cout << "1! = " << largeFactorial(1) << endl;
    cout << "Negative number: " << largeFactorial(-5) << endl;
    
    return 0;
}