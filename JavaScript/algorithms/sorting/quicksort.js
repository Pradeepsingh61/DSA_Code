/* Quick Sort

Description: Quick sort is a divide-and-conquer algorithm that works by selecting a 'pivot' element from the array and partitioning the other elements into two sub-arrays according to whether they are less than or greater than the pivot. The sub-arrays are then sorted recursively.

Time Complexity:
- Best/Average Case: O(n log n)
- Worst Case: O(n²)

Space Complexity: O(log n)
*/

function quickSort(arr) {
  if (arr.length <= 1) {
    return arr;
  }

  const pivot = arr[Math.floor(arr.length / 2)];
  const left = [];
  const right = [];
  const equal = [];

  for (let element of arr) {
    if (element < pivot) {
      left.push(element);
    } else if (element > pivot) {
      right.push(element);
    } else {
      equal.push(element);
    }
  }

  return [...quickSort(left), ...equal, ...quickSort(right)];
}

function runTests() {
  console.log("---------- Quick Sort Test Cases ----------");

  // Test 1: Regular unsorted array
  const test1 = [64, 34, 25, 12, 22, 11, 90];
  console.log("\nTest 1 - Original:", test1);
  console.log("Test 1 - Sorted:", quickSort(test1));

  // Test 2: Already sorted array
  const test2 = [1, 2, 3, 4, 5];
  console.log("\nTest 2 - Original:", test2);
  console.log("Test 2 - Sorted:", quickSort(test2));

  // Test 3: Reverse sorted array
  const test3 = [5, 4, 3, 2, 1];
  console.log("\nTest 3 - Original:", test3);
  console.log("Test 3 - Sorted:", quickSort(test3));

  // Test 4: Array with duplicates
  const test4 = [3, 1, 4, 1, 5, 9, 2, 6, 5];
  console.log("\nTest 4 - Original:", test4);
  console.log("Test 4 - Sorted:", quickSort(test4));

  // Test 5: Single element array
  const test5 = [42];
  console.log("\nTest 5 - Original:", test5);
  console.log("Test 5 - Sorted:", quickSort(test5));

  // Test 6: Empty array
  const test6 = [];
  console.log("\nTest 6 - Original:", test6);
  console.log("Test 6 - Sorted:", quickSort(test6));

  // Test 7: Large array
  const test7 = [38, 27, 43, 3, 9, 82, 10];
  console.log("\nTest 7 - Original:", test7);
  console.log("Test 7 - Sorted:", quickSort(test7));

  // Test 8: Array with negative numbers
  const test8 = [-5, 2, -3, 8, -1, 0];
  console.log("\nTest 8 - Original:", test8);
  console.log("Test 8 - Sorted:", quickSort(test8));
}

runTests();
