// Question: Linear Search using Recursion

#include <iostream>
using namespace std;

int linearSearch(int arr[], int n, int key, int index)
{
    if (index == n) // Base case: If the element is not found
        return -1;
    if (arr[index] == key) // If the element is found
        return index;
    return linearSearch(arr, n, key, index + 1); // Recursive call
}

int main()
{
    int n, key;
    cout << "Enter the number of elements in the array: ";
    cin >> n; // Input the number of elements in the array
    int arr[n];
    cout << "Enter the elements of the array: ";
    for (int i = 0; i < n; i++)
        cin >> arr[i]; // Input the elements of the array
    cout << "Enter the element to search: ";
    cin >> key; // Input the element to search
    int index = linearSearch(arr, n, key, 0); // Function call
    if (index != -1)
        cout << "Element found at index: " << index << endl; // Output if element is found
    else
        cout << "Element not found" << endl; // Output if element is not found
    return 0;
}

/*
**Explanation:**

1. Function Declaration (linearSearch)

The function linearSearch is declared with four parameters:
arr[]: the array containing the elements.
n: the number of elements in the array or the current size of the array for each recursive call.
key: the element to search in the array.
index: the current index being checked in the array.

2. Base Case (if (index == n))
The base case checks if the current index is equal to the size of the array (n). If the index reaches n, it means the element is not found in the array, and the function returns -1.

3. Recursive Call (linearSearch(arr, n, key, index + 1))
If the element is not found at the current index, the function makes a recursive call with the next index (index + 1) to search for the element in the remaining array.

4. Main Function

Input:
The program first asks the user for the number of elements (n) in the array.
Then, the user is prompted to enter the elements of the array one by one.
The user is also asked to enter the element (key) to search in the array.

Output:
The linearSearch function is called with the entire array, its size (n), the element to search (key), and the starting index (0).
If the element is found, the function returns the index where the element is found, and the program outputs "Element found at index: <index>".
If the element is not found, the function returns -1, and the program outputs "Element not found".


## Example Walkthrough:

If the input is:
n = 5
arr = [10, 20, 30, 40, 50]
key = 30
The recursive process looks like this:
linearSearch(arr, 5, 30, 0) = linearSearch(arr, 5, 30, 1)
linearSearch(arr, 5, 30, 1) = linearSearch(arr, 5, 30, 2)
linearSearch(arr, 5, 30, 2) = 2 (element found at index 2)
Output:
Element found at index: 2
*/