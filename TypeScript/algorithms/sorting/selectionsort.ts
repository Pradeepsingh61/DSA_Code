/* Selection Sort

Description: Selection sort is a simple comparison-based sorting algorithm. It works by repeatedly finding the minimum element from the unsorted portion of the array and placing it at the beginning. The algorithm divides the array into two parts: sorted and unsorted. In each iteration, it selects the smallest element from the unsorted part and swaps it with the first element of the unsorted part.

Time Complexity: O(n²)

Space Complexity: O(1)
*/

function selectionSort(arr: number[]): number[] {
  const n: number = arr.length;

  for (let i = 0; i < n - 1; i++) {
    let minIndex: number = i;

    for (let j = i + 1; j < n; j++) {
      if (arr[j] < arr[minIndex]) {
        minIndex = j;
      }
    }

    // Swap the found minimum element with the first element
    if (minIndex !== i) {
      [arr[i], arr[minIndex]] = [arr[minIndex], arr[i]];
    }
  }

  return arr;
}

function runTests(): void {
  console.log("---------- Selection Sort Test Cases ----------");

  // Test 1: Regular unsorted array
  const test1: number[] = [64, 34, 25, 12, 22, 11, 90];
  console.log("\nTest 1 - Original:", [...test1]);
  console.log("Test 1 - Sorted:", selectionSort([...test1]));

  // Test 2: Already sorted array
  const test2: number[] = [1, 2, 3, 4, 5];
  console.log("\nTest 2 - Original:", [...test2]);
  console.log("Test 2 - Sorted:", selectionSort([...test2]));

  // Test 3: Reverse sorted array
  const test3: number[] = [5, 4, 3, 2, 1];
  console.log("\nTest 3 - Original:", [...test3]);
  console.log("Test 3 - Sorted:", selectionSort([...test3]));

  // Test 4: Array with duplicates
  const test4: number[] = [3, 1, 4, 1, 5, 9, 2, 6, 5];
  console.log("\nTest 4 - Original:", [...test4]);
  console.log("Test 4 - Sorted:", selectionSort([...test4]));

  // Test 5: Single element array
  const test5: number[] = [42];
  console.log("\nTest 5 - Original:", [...test5]);
  console.log("Test 5 - Sorted:", selectionSort([...test5]));

  // Test 6: Empty array
  const test6: number[] = [];
  console.log("\nTest 6 - Original:", [...test6]);
  console.log("Test 6 - Sorted:", selectionSort([...test6]));

  // Test 7: Two element array
  const test7: number[] = [2, 1];
  console.log("\nTest 7 - Original:", [...test7]);
  console.log("Test 7 - Sorted:", selectionSort([...test7]));

  // Test 8: Array with negative numbers
  const test8: number[] = [-5, 2, -3, 8, -1, 0];
  console.log("\nTest 8 - Original:", [...test8]);
  console.log("Test 8 - Sorted:", selectionSort([...test8]));
}

runTests();
