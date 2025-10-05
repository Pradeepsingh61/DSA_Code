#include <stdio.h>

/*
* quick_sort : it takes the array, starting index, and ending index. It 
* recursively partitions the array around a pivot element, placing smaller 
* elements to the left and larger elements to the right, until the whole 
* array is sorted.
* @param arr: Array to process
* @param low: Starting index of the array/sub-array
* @param high: Ending index of the array/sub-array
* @return: None
*/


// Function to swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function
// This function places the pivot element at the correct position
// and places smaller elements to left and greater elements to right
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // Choosing last element as pivot
    int i = low - 1; // Index of smaller element
    
    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than or equal to pivot
        if (arr[j] <= pivot) {
            i++; // Increment index of smaller element
            swap(&arr[i], &arr[j]); // Swap it with current element
        }
    }
    // Place pivot at the correct position
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Quick Sort function
// Recursively sorts the array
void quickSort(int arr[], int low, int high) {
    //If array pointer is NULL, skip sorting
    if (arr == NULL || low >= high){
        return;
    }
    if (low < high) {
        // pi is partitioning index
        int pi = partition(arr, low, high);
        
        // Recursively sort elements before partition
        quickSort(arr, low, pi - 1);
        
        // Recursively sort elements after partition
        quickSort(arr, pi + 1, high);
    }
}

// Function to print the array
void printArray(int arr[], int size) {
    //If size <= 0, don’t process
    if (arr == NULL || size <= 0) {
        printf("empty array.\n");
        return;
    }

    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Main function
int main() {
    // Array for test case 
    int arr[] = {10, 7, 8, 9, 1, 5};
    // Size of array
    int n = sizeof(arr)/sizeof(arr[0]);
    
    // Print origanal array
    printf("Original array: ");
    printArray(arr, n);
    
    // Call quick sort function
    quickSort(arr, 0, n - 1);

    //Print sorted array
    printf("Sorted array:   ");
    printArray(arr, n);
    
    return 0;
}

/*
 * Algorithm: Quick Sort
 * Description: Quick Sort is a divide-and-conquer algorithm. It selects a 
 *               'pivot' element from the array and partitions the other 
 *               elements into two sub-arrays, according to whether they are 
 *               less than or greater than the pivot. The sub-arrays are then 
 *               sorted recursively.
 * Time Complexity:
 *       Best Case    : O(n log n)
 *       Average Case : O(n log n)
 *       Worst Case   : O(n^2)
 * Space Complexity: O(log n) due to recursive stack calls
 * Author: subhahens
 */