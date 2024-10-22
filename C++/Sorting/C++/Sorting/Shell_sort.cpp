#include <iostream>
using namespace std;

// Function to perform Shell Sort
void shellSort(int arr[], int n) {
    // Start with a large gap, then reduce the gap
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // Perform a gapped insertion sort for this gap size
        for (int i = gap; i < n; i++) {
            // Store current element in temp and create a hole at i
            int temp = arr[i];
            int j;

            // Shift elements of arr[0..i-gap], that are greater than temp, to the right
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];  // Shift element to the right
            }

            // Place temp (the original arr[i]) in its correct location
            arr[j] = temp;
        }
    }
}

int main() {
    // Initialize the array
    int arr[] = {12, 34, 54, 2, 3};
    int n = sizeof(arr) / sizeof(arr[0]);  // Calculate size of the array

    // Call the shellSort function to sort the array
    shellSort(arr, n);

    // Print the sorted array
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";  // Output each element
    }

    return 0;
}
