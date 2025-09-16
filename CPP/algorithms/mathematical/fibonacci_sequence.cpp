#include <iostream>  // Include for input and output streams
#include <vector>   // Include for using vectors

using namespace std; // Use the standard namespace to avoid prefixing with std::
 /*
     * Explanation of Fibonacci Sequence:
     * The Fibonacci sequence is a series of numbers where each number 
     * (after the first two) is the sum of the two preceding ones.
     * It typically starts with 0 and 1.
     * Example: The first 10 Fibonacci numbers are:
     * 0, 1, 1, 2, 3, 5, 8, 13, 21, 34
   */
/*
 * Function to generate Fibonacci sequence using the iterative approach.
 * Takes an integer n as input and returns a vector containing the first n Fibonacci numbers.
 */
vector<int> fibonacci_iterative(int n) {
    vector<int> fib_sequence;  // Vector to store Fibonacci numbers

    // Return empty vector for non-positive input
    if (n <= 0) return fib_sequence; 
    // If n is 1, return vector with the first Fibonacci number
    else if (n == 1) {
        fib_sequence.push_back(0);
        return fib_sequence;
    } 
    // If n is 2, return vector with the first two Fibonacci numbers
    else if (n == 2) {
        fib_sequence.push_back(0);
        fib_sequence.push_back(1);
        return fib_sequence;
    }

    fib_sequence.push_back(0);  // First Fibonacci number
    fib_sequence.push_back(1);  // Second Fibonacci number

    // Loop to calculate the rest of the Fibonacci numbers
    for (int i = 2; i < n; ++i) {
        // Calculate the next Fibonacci number as the sum of the last two
        int next_fib = fib_sequence[i - 1] + fib_sequence[i - 2]; 
        fib_sequence.push_back(next_fib); // Add the next Fibonacci number to the sequence
    }

    return fib_sequence; // Return the complete Fibonacci sequence
}

int main() {
    int n; // Variable to hold the number of Fibonacci numbers to generate
    cout << "Enter the number of Fibonacci numbers to generate: ";
    cin >> n; // Input from the user

    // Generate the Fibonacci sequence
    vector<int> fib_sequence = fibonacci_iterative(n);

    // Output the generated Fibonacci sequence
    cout << "The first " << n << " Fibonacci numbers are: ";
    for (int num : fib_sequence) {
        cout << num << " "; // Print each number in the sequence
    }
    cout << endl; // Print a newline after output

   

    return 0; // End of the program
}
