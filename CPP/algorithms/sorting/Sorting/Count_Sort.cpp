/*
 * Counting Sort Implementation
 * 
 * Algorithm Overview:
 * Counting sort is a non-comparison based sorting algorithm that works by counting
 * the occurrences of each distinct element and using this information to place
 * elements directly in their correct sorted position.
 * 
 * Time Complexity: O(n + k) where n is number of elements, k is range of input
 * Space Complexity: O(k) for the counting array
 * 
 * Best suited for: Integer arrays with small range of values
 * Characteristics: Stable sorting algorithm, not in-place
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * Counting Sort function for integer arrays
 * 
 * @param arr[] - Array of integers to be sorted (non-negative integers)
 * @param n - Size of the array
 * 
 * Algorithm Steps:
 * 1. Find the maximum element to determine the range
 * 2. Create counting array to store frequency of each element
 * 3. Store count of each element in the counting array
 * 4. Modify counting array to store cumulative counts (positions)
 * 5. Build output array using counting array (ensures stability)
 * 6. Copy sorted elements back to original array
 */
void countSort(int arr[], int n) {
    // Step 1: Find the maximum element to determine the range of values
    // This helps us create a counting array of appropriate size
    int maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxVal)
            maxVal = arr[i];
    }

    // Step 2: Create auxiliary arrays
    // count[]: stores frequency of each element (size = maxVal + 1)
    // output[]: temporary array to build sorted result
    vector<int> count(maxVal + 1, 0);  // Initialize all counts to 0
    vector<int> output(n);             // Output array of same size as input

    // Step 3: Store count/frequency of each element
    // count[i] will contain the number of times element 'i' appears
    for (int i = 0; i < n; i++)
        count[arr[i]]++;

    // Step 4: Transform count array to store cumulative counts
    // Now count[i] contains the number of elements <= i
    // This gives us the position where each element should be placed
    for (int i = 1; i <= maxVal; i++)
        count[i] += count[i - 1];

    // Step 5: Build the output array (traverse from right to maintain stability)
    // Traversing from right ensures that if there are duplicate elements,
    // the one that appears later in the original array appears later in sorted array
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];  // Place element at correct position
        count[arr[i]]--;                     // Decrement count for next occurrence
    }

    // Step 6: Copy sorted elements back to original array
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

/**
 * Utility function to print array elements
 * 
 * @param arr[] - Array to be printed
 * @param size - Number of elements in the array
 */
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

/**
 * Main function - Entry point of the program
 * Demonstrates counting sort with a sample array of integers
 */
int main() {
    // Sample array with non-negative integers
    // Note: Counting sort works best when the range (max - min) is small
    int arr[] = {4, 2, 2, 8, 3, 3, 1};
    
    // Calculate array size using sizeof operator
    int n = sizeof(arr) / sizeof(arr[0]);

    // Display original array
    cout << "Original Array: ";
    printArray(arr, n);

    // Perform counting sort
    countSort(arr, n);

    // Display sorted result
    cout << "Sorted Array (Counting Sort): ";
    printArray(arr, n);

    // Display algorithm characteristics
    cout << "\nCounting Sort Characteristics:" << endl;
    cout << "- Time Complexity: O(n + k) where k is range of input" << endl;
    cout << "- Space Complexity: O(k) for counting array" << endl;
    cout << "- Stable: Yes (maintains relative order of equal elements)" << endl;
    cout << "- In-place: No (requires additional space)" << endl;
    cout << "- Best for: Integer arrays with small range of values" << endl;
    cout << "- Limitation: Only works with non-negative integers" << endl;

    return 0;
}
