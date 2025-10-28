/*
* Algorithm: [Binary Search]
 * Description: [Binary search is an efficient algorithm used to find the position of a target value within a sorted array or list. It works on the principle of repeatedly dividing the search interval in half.]
 * Time Complexity :
 *     Best Case : O(1)  // when given array is already sorted.
 *     Average Case : O(log n) //when given array is in random order
 *     Worst Case : O(log n) // when given array is in reverse order
 * Space Complexity:
 *   Worst : 0(1)
 * Author: [Kaustubh Udavant]
 */

#include <stdio.h>
//function to perform binary search
int binarySearch(int arr[], int size, int key) {
    int low = 0, high = size - 1, mid;

    while (low <= high) {
        mid = (low + high) / 2;

        if (arr[mid] == key)
            return mid;
        else if (key < arr[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }

    return -1;
}
int main() {
    int size, key, position;

    printf("Enter the number of elements: ");
    scanf("%d", &size);

    int arr[size];

    printf("Enter %d elements in ascending order:\n", size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter the number to search: ");
    scanf("%d", &key);

    position = binarySearch(arr, size, key);

    if (position == -1)
        printf("The number %d was not found in the array.\n", key);
    else
        printf("The number %d was found at index %d (position %d).\n", key, position, position + 1);

    return 0;
}

