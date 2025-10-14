/* Binary Search

Description: Binary Search finds the position of a target element in a sorted array by repeatedly dividing the search interval in half. If the value of the search key is less than the item in the middle of the interval, it narrows the interval to the lower half. Otherwise, it narrows it to the upper half. The search continues until the value is found or the interval is empty.

Prerequisites: The input array must be sorted in ascending order

Time Complexity: O(log n)
Space Complexity:
- Iterative: O(1) - constant space
- Recursive: O(log n) - due to call stack

*/

function binarySearchIterative<T>(arr: T[], target: T): number {
  let left: number = 0;
  let right: number = arr.length - 1;

  while (left <= right) {
    const mid: number = Math.floor(left + (right - left) / 2);

    if (arr[mid] === target) {
      return mid;
    }

    if (arr[mid] < target) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }

  return -1;
}

function binarySearchRecursive<T>(
  arr: T[],
  target: T,
  left: number = 0,
  right: number = arr.length - 1
): number {
  if (left > right) {
    return -1;
  }

  const mid: number = Math.floor(left + (right - left) / 2);

  if (arr[mid] === target) {
    return mid;
  }

  if (arr[mid] < target) {
    return binarySearchRecursive(arr, target, mid + 1, right);
  } else {
    return binarySearchRecursive(arr, target, left, mid - 1);
  }
}

const sortedArray: number[] = [1, 3, 5, 7, 9, 11, 13, 15, 17, 19];

function runTests(): void {
  console.log("---------- Binary Search Test Cases ----------");

  console.log("\nIterative Binary Search:");
  console.log(`Finding 7: Index ${binarySearchIterative(sortedArray, 7)}`); // Should return 3
  console.log(`Finding 15: Index ${binarySearchIterative(sortedArray, 15)}`); // Should return 7
  console.log(`Finding 4: Index ${binarySearchIterative(sortedArray, 4)}`); // Should return -1

  console.log("\nRecursive Binary Search:");
  console.log(`Finding 7: Index ${binarySearchRecursive(sortedArray, 7)}`); // Should return 3
  console.log(`Finding 15: Index ${binarySearchRecursive(sortedArray, 15)}`); // Should return 7
  console.log(`Finding 4: Index ${binarySearchRecursive(sortedArray, 4)}`); // Should return -1
}

runTests();
