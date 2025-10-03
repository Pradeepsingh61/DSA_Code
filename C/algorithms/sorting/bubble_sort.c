/*
 * Algorithm: [Bubble Sort]
 * Description: [It starts from the beginning of the list and compares each
 *               pair of adjacent elements, and swap them if they are in the
 *               wrong order]
 * Time Complexity :
 *     Best Case : O(n)  // when given array is already sorted.
 *     Average Case : O(n^2) //when given array is in random order
 *     Worst Case : O(n^2) // when given array is in reverse order
 * Space Complexity:
 *   Worst : 0(1)
 * Author: [tanshen-kun]
 */

#include <stdio.h>

/*
 * bubble_sort : it takse the array and its size then it starts to travel array
 * while comparing successive pairs of element until the travel reach the last
 * element
 * @param arr: Array to process
 * @param size: Size of the array
 * @return: None
 */

void bubble_sort(int arr[], int size) {
  for (int i = 0; i < size - 1; i++) {
    for (int j = 0; j < size - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}

/*
 * printArray: Prints a given array
 *
 *@param arr: Array to print
 *@param size: Size of the array
 */
void printArray(int arr[], int size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

void test_algorithm() {
  printf("Testing Algorithm...\n");

  // Test Case 1 : Already Sorted
  int test_arr1[] = {1, 2, 3, 4, 5};
  int size1 = sizeof(test_arr1) / sizeof(test_arr1[0]);
  printf("Test 1 : ");
  bubble_sort(test_arr1, size1);
  printArray(test_arr1, size1);

  // Test Case 2 : Random order
  int test_arr2[] = {3, 1, 5, 2, 4};
  int size2 = sizeof(test_arr2) / sizeof(test_arr2[0]);
  printf("Test 2 : ");
  bubble_sort(test_arr2, size2);
  printArray(test_arr2, size2);

  // Test Case 3 : Reverse Order
  int test_arr3[] = {5, 4, 3, 2, 1};
  int size3 = sizeof(test_arr3) / sizeof(test_arr3[0]);
  printf("Test 3 : ");
  bubble_sort(test_arr3, size3);
  printArray(test_arr3, size3);
}

int main() {
  test_algorithm();
  return 0;
}
