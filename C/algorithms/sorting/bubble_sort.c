// Bubble Sort Implementation in C
// Hacktoberfest 2025 Contribution

#include <stdio.h>

// Function prototypes
void inputArray(int arr[], int size);
void displayArray(int arr[], int size);
void bubbleSort(int arr[], int size);

int main() {
    int size;

    printf("Enter the number of elements: ");
    scanf("%d", &size);

    int arr[size];

    // Get input from user
    inputArray(arr, size);

    printf("\nOriginal array:\n");
    displayArray(arr, size);

    // Sort array using Bubble Sort
    bubbleSort(arr, size);

    printf("\nSorted array in ascending order:\n");
    displayArray(arr, size);

    return 0;
}

// Reads 'size' number of elements into the array
void inputArray(int arr[], int size) {
    printf("Enter %d elements:\n", size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }
}

// Displays the contents of the array
void displayArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Performs Bubble Sort on the array
void bubbleSort(int arr[], int size) {
    int temp;
    int swapped;

    for (int i = 0; i < size - 1; i++) {
        swapped = 0;

        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap elements
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }

        // Optimization: stop if array is already sorted
        if (!swapped)
            break;
    }
}
