/* Bubble Sort

Description: Bubble sort is a simple sorting algorithm that repeatedly steps through the list, compares adjacent elements and swaps them if they are in the wrong order. The pass through the list is repeated until the list is sorted.

Time Complexity:
- Best Case: O(n) - Sorted array
- Average and Worst Case: O(n²)

Space Complexity: O(1)
*/

function bubbleSort(arr: number[]): number[] {
  const n: number = arr.length;

  for (let i = 0; i < n - 1; i++) {
    let swapped: boolean = false;

    for (let j = 0; j < n - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        [arr[j], arr[j + 1]] = [arr[j + 1], arr[j]];
        swapped = true;
      }
    }

    if (!swapped) break;
  }

  return arr;
}

function runTests(): void {
  console.log("---------- Bubble Sort Test Cases ----------");

  // Test 1: Regular unsorted array
  const test1: number[] = [64, 34, 25, 12, 22, 11, 90];
  console.log("\nTest 1 - Original:", test1);
  console.log("Test 1 - Sorted:", bubbleSort(test1));

  // Test 2: Already sorted array
  const test2: number[] = [1, 2, 3, 4, 5];
  console.log("\nTest 2 - Original:", test2);
  console.log("Test 2 - Sorted:", bubbleSort(test2));

  // Test 3: Reverse sorted array
  const test3: number[] = [5, 4, 3, 2, 1];
  console.log("\nTest 3 - Original:", test3);
  console.log("Test 3 - Sorted:", bubbleSort(test3));

  // Test 4: Array with duplicates
  const test4: number[] = [3, 1, 4, 1, 5, 9, 2, 6, 5];
  console.log("\nTest 4 - Original:", test4);
  console.log("Test 4 - Sorted:", bubbleSort(test4));

  // Test 5: Single element array
  const test5: number[] = [42];
  console.log("\nTest 5 - Original:", test5);
  console.log("Test 5 - Sorted:", bubbleSort(test5));

  // Test 6: Empty array
  const test6: number[] = [];
  console.log("\nTest 6 - Original:", test6);
  console.log("Test 6 - Sorted:", bubbleSort(test6));
}

runTests();
