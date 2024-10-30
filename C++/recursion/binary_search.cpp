// Binary Search using Recursion

#include <iostream>
using namespace std;

int binarySearch(int arr[], int low, int high, int key)
{
    if (low > high) // Base case: If the element is not found
        return -1;
    int mid = low + (high - low) / 2; // Calculate the middle index
    if (arr[mid] == key) // If the element is found at the middle index
        return mid;
    if (arr[mid] > key) // If the key is smaller, search in the left half
        return binarySearch(arr, low, mid - 1, key);
    return binarySearch(arr, mid + 1, high, key); // Search in the right half
}

int main()
{
    int n, key;
    cout << "Enter the number of elements in the array: ";
    cin >> n; // Input the number of elements in the array
    int arr[n];
    cout << "Enter the elements of the array in sorted order: ";
    for (int i = 0; i < n; i++)
        cin >> arr[i]; // Input the elements of the array
    cout << "Enter the element to search: ";
    cin >> key; // Input the element to search
    int index = binarySearch(arr, 0, n - 1, key); // Function call
    if (index != -1)
        cout << "Element found at index: " << index << endl; // Output if element is found
    else
        cout << "Element not found" << endl; // Output if element is not found
    return 0;
}


/*
**Explanation:**

1. Function Declaration (binarySearch)

The function binarySearch is declared with four parameters:
arr[]: the array containing the elements.
low: the starting index of the array.
high: the ending index of the array.
key: the element to search in the array.

2. Base Case (if (low > high))

The base case checks if the starting index (low) is greater than the ending index (high). If low becomes greater than high, it means the element is not found in the array, and the function returns -1.

3. Calculate the Middle Index
The middle index (mid) is calculated as the average of the low and high indices to divide the array into two halves.

4. Check if the Element is Found
If the element is found at the middle index, the function returns the index.

5. Recursive Calls
If the element is not found at the middle index, the function makes a recursive call to search in the left half if the key is smaller than the middle element (arr[mid]). Otherwise, it searches in the right half.

6. Main Function

Input:
The program first asks the user for the number of elements (n) in the array.
Then, the user is prompted to enter the elements of the array in sorted order.
The user is also asked to enter the element (key) to search in the array.

Output:
The binarySearch function is called with the entire array, the starting index (0), the ending index (n - 1), and the element to search (key).
If the element is found, the function returns the index where the element is found, and the program outputs "Element found at index: <index>".
If the element is not found, the function returns -1, and the program outputs "Element not found".


Example Walkthrough:

If the input is:
n = 5
arr = [2, 4, 6, 8, 10]
key = 8
The recursive process looks like this:
binarySearch(arr, 0, 4, 8) = binarySearch(arr, 3, 4, 8)
binarySearch(arr, 3, 4, 8) = binarySearch(arr, 3, 3, 8)
Finally, the element 8 is found at index 3.
*/