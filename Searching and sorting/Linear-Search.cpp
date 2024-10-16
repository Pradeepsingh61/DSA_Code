#include <iostream>
using namespace std;

// Function to perform Linear Search
int linearSearch(int arr[], int size, int target) {
    // Iterate through the entire array
    for (int i = 0; i < size; i++) {
        // Check if the current element matches the target
        if (arr[i] == target) {
            return i; // Return the index of the target element
        }
    }
    return -1; // Return -1 if the target is not found
}

int main() {
    int arr[] = {34, 78, 21, 56, 11, 9, 45};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 56;

    // Call the linear search function
    int result = linearSearch(arr, size, target);

    // Output the result
    if (result != -1) {
        cout << "Element found at index: " << result << endl;
    } else {
        cout << "Element not found!" << endl;
    }

    return 0;
}
