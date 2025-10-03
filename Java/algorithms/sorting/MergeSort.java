/*
 * Algorithm Name
Merge Sort
     
Programming Language
Java

Category
Sorting

Difficulty Level
Medium

* Algorithm Description :

1. Problem it solves:
-> Efficiently sorts an array or list in ascending order.
-> Works better than simple algorithms (like Bubble Sort or Insertion Sort) for large datasets.

2. Approach / Idea:
-> Merge Sort is a Divide and Conquer algorithm.
-> Steps:
   - Divide: Split the array into two halves.
   - Conquer: Recursively sort the two halves.
   - Combine: Merge the two sorted halves into one sorted array.

3. Complexity:
Time:
-> Best Case: O(n log n)
-> Average Case: O(n log n)
-> Worst Case: O(n log n)

Space:
-> O(n) for temporary arrays during merging.

* Author : Surya Pratap Singh
*/

public class MergeSort {
    void merge(int arr[], int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        int L[] = new int[n1];
        int R[] = new int[n2];

        for (int i = 0; i < n1; ++i)
            L[i] = arr[left + i];
        for (int j = 0; j < n2; ++j)
            R[j] = arr[mid + 1 + j];

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }

        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
        }
    }

    // Function to sort array using merge sort
    void sort(int arr[], int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;

            sort(arr, left, mid);
            sort(arr, mid + 1, right);

            merge(arr, left, mid, right);
        }
    }

    // Driver function
    public static void main(String args[]) {
        int arr[] = {12, 11, 13, 5, 6, 7};

        MergeSort ob = new MergeSort();
        ob.sort(arr, 0, arr.length - 1);

        System.out.println("Sorted array:");
        for (int num : arr)
            System.out.print(num + " ");
    }
}
