/* Merge Sort

Description: Merge sort is a divide-and-conquer algorithm that divides the input array into two halves, calls itself for the two halves, and then merges the two sorted halves. The merge() function is used for merging two halves.

Time Complexity: O(n log n)

Space Complexity: O(n)
*/

function mergeSort(arr) {
  if (arr.length <= 1) {
    return arr;
  }

  const middle = Math.floor(arr.length / 2);
  const leftList = arr.slice(0, middle);
  const rightList = arr.slice(middle);

  return merge(mergeSort(leftList), mergeSort(rightList));
}

function merge(leftList, rightList) {
  let result = [];
  let left = 0;
  let right = 0;

  while (left < leftList.length && right < rightList.length) {
    if (leftList[left] < rightList[right]) {
      result.push(leftList[left]);
      left++;
    } else {
      result.push(rightList[right]);
      right++;
    }
  }

  return result.concat(leftList.slice(left)).concat(rightList.slice(right));
}

function runTests() {
  console.log("---------- Merge Sort Test Cases ----------");

  // Test 1: Regular unsorted array
  const test1 = [64, 34, 25, 12, 22, 11, 90];
  console.log("\nTest 1 - Original:", test1);
  console.log("Test 1 - Sorted:", mergeSort(test1));

  // Test 2: Already sorted array
  const test2 = [1, 2, 3, 4, 5];
  console.log("\nTest 2 - Original:", test2);
  console.log("Test 2 - Sorted:", mergeSort(test2));

  // Test 3: Reverse sorted array
  const test3 = [5, 4, 3, 2, 1];
  console.log("\nTest 3 - Original:", test3);
  console.log("Test 3 - Sorted:", mergeSort(test3));

  // Test 4: Array with duplicates
  const test4 = [3, 1, 4, 1, 5, 9, 2, 6, 5];
  console.log("\nTest 4 - Original:", test4);
  console.log("Test 4 - Sorted:", mergeSort(test4));

  // Test 5: Single element array
  const test5 = [42];
  console.log("\nTest 5 - Original:", test5);
  console.log("Test 5 - Sorted:", mergeSort(test5));

  // Test 6: Empty array
  const test6 = [];
  console.log("\nTest 6 - Original:", test6);
  console.log("Test 6 - Sorted:", mergeSort(test6));

  // Test 7: Large array
  const test7 = [38, 27, 43, 3, 9, 82, 10];
  console.log("\nTest 7 - Original:", test7);
  console.log("Test 7 - Sorted:", mergeSort(test7));
}

runTests();
