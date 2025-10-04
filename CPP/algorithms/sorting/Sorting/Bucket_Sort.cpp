/*
 * Bucket Sort Implementation
 * 
 * Algorithm Overview:
 * Bucket sort is a sorting algorithm that works by distributing elements into buckets,
 * sorting each bucket individually, and then concatenating the sorted buckets.
 * 
 * Time Complexity:
 * - Best/Average Case: O(n + k) where n is number of elements, k is number of buckets
 * - Worst Case: O(n²) when all elements fall into the same bucket
 * 
 * Space Complexity: O(n + k)
 * 
 * Best suited for: Uniformly distributed floating-point numbers in range [0.0, 1.0)
 */

#include <iostream>
#include <vector>
#include <algorithm>  // for sort() function
using namespace std;

/**
 * Bucket Sort function for floating-point numbers in range [0.0, 1.0)
 * 
 * @param arr[] - Array of floating-point numbers to be sorted
 * @param n - Size of the array
 * 
 * Assumption: All elements are in range [0.0, 1.0)
 */
void bucketSort(float arr[], int n) {
    // Step 1: Create n empty buckets (using vector for dynamic sizing)
    // Each bucket will store elements that fall within a specific range
    vector<float> buckets[n];

    // Step 2: Distribute array elements into different buckets
    // Formula: bucket_index = floor(n * element_value)
    // This ensures uniform distribution when elements are uniformly distributed
    for (int i = 0; i < n; i++) {
        int index = n * arr[i]; // Multiply by n to get bucket index (implicit floor)
        buckets[index].push_back(arr[i]); // Add element to appropriate bucket
    }

    // Step 3: Sort individual buckets using standard library sort
    // Since each bucket typically contains few elements, this is efficient
    for (int i = 0; i < n; i++) {
        sort(buckets[i].begin(), buckets[i].end());
    }

    // Step 4: Concatenate all sorted buckets back into original array
    // Process buckets in order (0 to n-1) to maintain sorted order
    int idx = 0; // Index for placing elements back in original array
    for (int i = 0; i < n; i++) {
        // Copy all elements from current bucket to original array
        for (float val : buckets[i]) {
            arr[idx++] = val;
        }
    }
}

/**
 * Utility function to print array elements
 * 
 * @param arr[] - Array to be printed
 * @param size - Number of elements in array
 */
void printArray(float arr[], int size) {
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

/**
 * Main function - Entry point of the program
 * Demonstrates bucket sort with a sample array of floating-point numbers
 */
int main() {
    // Sample array with floating-point numbers in range [0.0, 1.0)
    // Note: All values must be between 0.0 and 1.0 for this implementation
    float arr[] = {0.78, 0.17, 0.39, 0.26, 0.72, 0.94, 0.21, 0.12, 0.23, 0.68};
    
    // Calculate array size using sizeof operator
    int n = sizeof(arr) / sizeof(arr[0]);

    // Display original array
    cout << "Original Array: ";
    printArray(arr, n);

    // Perform bucket sort
    bucketSort(arr, n);

    // Display sorted result
    cout << "Sorted Array (Bucket Sort): ";
    printArray(arr, n);

    // Display algorithm information
    cout << "\nBucket Sort Characteristics:" << endl;
    cout << "- Time Complexity: O(n + k) average, O(n²) worst case" << endl;
    cout << "- Space Complexity: O(n + k)" << endl;
    cout << "- Stable: Yes (depends on sorting algorithm used for buckets)" << endl;
    cout << "- In-place: No" << endl;
    cout << "- Best for: Uniformly distributed floating-point data" << endl;

    return 0;
}
