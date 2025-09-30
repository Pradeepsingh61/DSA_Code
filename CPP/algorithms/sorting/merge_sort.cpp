/**
 * Merge Sort Algorithm
 *
 * A divide-and-conquer algorithm that divides the input array into two halves,
 * recursively sorts them, and then merges the sorted halves.
 *
 * Time Complexity: O(n log n) in all cases
 * Space Complexity: O(n) for temporary array
 *
 * Author: Karanjot Singh
 * Date: September 2025
 
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * Merges two sorted subarrays into one sorted array
 *
 * @param arr The main array containing both subarrays
 * @param left Starting index of first subarray
 * @param mid Ending index of first subarray
 * @param right Ending index of second subarray
 */
void merge(vector<int>& arr, int left, int mid, int right) {
    // Calculate sizes of two subarrays
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    vector<int> leftArr(n1);
    vector<int> rightArr(n2);

    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    // Merge the temporary arrays back into arr[left..right]
    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements of leftArr[], if any
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    // Copy remaining elements of rightArr[], if any
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

/**
 * Main merge sort function that recursively divides and sorts the array
 *
 * @param arr The array to be sorted
 * @param left Starting index
 * @param right Ending index
 */
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        // Find the middle point
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

/**
 * Utility function to print an array
 */
void printArray(const vector<int>& arr) {
    for (int num : arr)
        cout << num << " ";
    cout << endl;
}

/**
 * Main function demonstrating merge sort usage
 */
int main() {
    vector<int> arr = {64, 34, 25, 12, 22, 11, 90};

    cout << "Original array: ";
    printArray(arr);

    mergeSort(arr, 0, arr.size() - 1);

    cout << "Sorted array: ";
    printArray(arr);

    return 0;
}

/*
Example Output:
Original array: 64 34 25 12 22 11 90
Sorted array: 11 12 22 25 34 64 90

Test Cases:
1. Empty array: [] -> []
2. Single element: [5] -> [5]
3. Already sorted: [1,2,3,4,5] -> [1,2,3,4,5]
4. Reverse sorted: [5,4,3,2,1] -> [1,2,3,4,5]
5. Duplicates: [3,1,3,2,1] -> [1,1,2,3,3]
*/