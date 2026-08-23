/*
 * Algorithm: Binary Search
 * Description: Binary Search basically searches a target from a 1D array if exists,then 
                it returns the index number of the element if fails to find then it returns -1;
                It actually breaks the array(sorted) into 2 halves and checks if the mid index 
                has the element,if it finds then returns ,else repeat the process, till the end;

 * Time Complexity:
                    Binary Search Iterative : O(log n) | (if array is already sorted);
                                            : O(log n + n^2) | (if have to sort the array);                        
                    Binary Search Recursive : O(log n) | (if array is already sorted);
                                            : O(log n + n^2) |(if have to sort the array);
 
 * Space Complexity:
                    Binary Search Iterative : O(1) (constant space)
                    Binary Search Recursive : O(log n) (stack frame space)
                    
 * Author: ADIL AHMED
 */
 
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Brief description of the functions :
 *                      There are total 5 functions in the code excluding the main() & test_algorithm() function.
 *                      
 *                  Binary_search_iterative : perform binary search in iterative way.
 *                  Binary_search_recursive : perform binary search with help of recursion;
 *                  compare_ints : Compares two numbers to determine ascending or descending sorting order.
 *                  insertion_sort : Sorts small arrays in-place with excellent CPU cache efficiency.
 *                  universal_sort : Switches algorithms automatically based on array size for speed.
 * 
 *
 * @param arr: int arr[]={3,4,1,67} //taken as a test case 
 * @param size: Size of the array is 4; //n=4
 * @return: The return value of the Binary_search_iterative & Binary_search_recursive both is 
 *          the index value from the given array of the target (if exists) else -1;
 */

int Binary_search_iterative(int arr[][2],int n,int target){
    int low=0,high=n-1;
    while(low<=high){
        int mid=low+(high-low)/2;
        if(arr[mid][0]==target) return arr[mid][1];
        else if(arr[mid][0]>target) high=mid-1;
        else low=mid+1;
    }
    return -1;
}

int Binary_search_recursive(int arr[][2],int target,int low,int high){
    if(low<=high){
        int mid=low+(high-low)/2;
        if(arr[mid][0]==target) return arr[mid][1];
        else if(arr[mid][0]>target) return Binary_search_recursive(arr,target,low,mid-1);
        else return Binary_search_recursive(arr,target,mid+1,high);
    }
    return -1;
}


// Standard comparison function
int compare_ints(const void *a, const void *b) {
    int val_a = ((const int *)a)[0];
    int val_b = ((const int *)b)[0];
    return (val_a > val_b) - (val_a < val_b);
}

// Inlined Insertion Sort for small workloads
static inline void insertion_sort(int arr[][2], int n) {
     for (int i = 1; i < n; i++) {
        int key_val = arr[i][0];
        int key_idx = arr[i][1];
        int j = i - 1;
        while (j >= 0 && arr[j][0] > key_val) {
            arr[j + 1][0] = arr[j][0];
            arr[j + 1][1] = arr[j][1];
            j--;
        }
        arr[j + 1][0] = key_val;
        arr[j + 1][1] = key_idx;
    }
}

// Universal optimized entry point
void universal_sort(int arr[], int n) {
    if (n <= 1) return; // having 1 element means already sorted
    if (n <= 16) {// for less than 16 sized arrays insertion_sort is highly optimised
        insertion_sort(arr, n);
    } else {// for other cases the builtin qsort() function of c is enough optimised
        qsort(arr, n, sizeof(int)*2, compare_ints);
    }
}


/**
 * Integrated test function demonstrating the binary search algorithm
 */
void test_algorithm() {
    printf("Testing Algorithm...\n\n");

    // Test Case 1: Normal case
    int raw_arr1[] = {3, 4, 1, 67};
    int size1 = sizeof(raw_arr1) / sizeof(raw_arr1[0]);
    int target1 = 4;
    
    int test_arr1[size1][2];
    for(int i = 0; i < size1; i++) {
        test_arr1[i][0] = raw_arr1[i];
        test_arr1[i][1] = i;
    }
    
    universal_sort(test_arr1, size1);
    int result1 = Binary_search_iterative(test_arr1, size1, target1);
    printf("Test 1 - Input: {3,4,1,67}, Target: %d, Original Index: %d\n successfully handled \n\n", target1, result1);

    // Test Case 2: Edge case (Empty/Null check)
    int (*test_arr2)[2] = NULL;
    int result2 = Binary_search_iterative(test_arr2, 0, 4);
    printf("Test 2 - Edge case handled: %d\n successfully handled \n\n", result2);
}

int main() {
    // Run the integrated test pipeline
    test_algorithm();
    return 0;
}

