/* Linear Search

Description: Linear Search finds the position of a target element in an array by checking each element sequentially from the beginning until the target is found or the end of the array is reached.

Time Complexity: O(n)
Space Complexity: O(1)
*/

function linearSearch<T>(arr: T[], target: T): number {
  if (!Array.isArray(arr)) {
    throw new Error("First argument must be an array");
  }

  for (let i = 0; i < arr.length; i++) {
    if (arr[i] === target) {
      return i;
    }
  }
  return -1;
}

function runTests(): void {
  console.log("---------- Linear Search Test Cases ----------");

  // Test Case 1: Element found
  const arr1: number[] = [5, 2, 8, 12, 1, 6];
  const target1: number = 8;
  const result1: number = linearSearch(arr1, target1);
  console.log(`Test 1 - Array: [${arr1}], Target: ${target1}`);
  console.log(
    `Expected: 2, Got: ${result1}, Status: ${result1 === 2 ? "PASS" : "FAIL"}\n`
  );

  // Test Case 2: Element not found
  const arr2: number[] = [1, 3, 5, 7, 9];
  const target2: number = 4;
  const result2: number = linearSearch(arr2, target2);
  console.log(`Test 2 - Array: [${arr2}], Target: ${target2}`);
  console.log(
    `Expected: -1, Got: ${result2}, Status: ${
      result2 === -1 ? "PASS" : "FAIL"
    }\n`
  );

  // Test Case 3: First element
  const arr3: number[] = [10, 20, 30, 40];
  const target3: number = 10;
  const result3: number = linearSearch(arr3, target3);
  console.log(`Test 3 - Array: [${arr3}], Target: ${target3}`);
  console.log(
    `Expected: 0, Got: ${result3}, Status: ${result3 === 0 ? "PASS" : "FAIL"}\n`
  );

  // Test Case 4: Last element
  const arr4: number[] = [15, 25, 35, 45];
  const target4: number = 45;
  const result4: number = linearSearch(arr4, target4);
  console.log(`Test 4 - Array: [${arr4}], Target: ${target4}`);
  console.log(
    `Expected: 3, Got: ${result4}, Status: ${result4 === 3 ? "PASS" : "FAIL"}\n`
  );

  // Test Case 5: Empty array
  const arr5: number[] = [];
  const target5: number = 1;
  const result5: number = linearSearch(arr5, target5);
  console.log(`Test 5 - Array: [${arr5}], Target: ${target5}`);
  console.log(
    `Expected: -1, Got: ${result5}, Status: ${
      result5 === -1 ? "PASS" : "FAIL"
    }\n`
  );

  // Test Case 6: Single element array (found)
  const arr6: number[] = [42];
  const target6: number = 42;
  const result6: number = linearSearch(arr6, target6);
  console.log(`Test 6 - Array: [${arr6}], Target: ${target6}`);
  console.log(
    `Expected: 0, Got: ${result6}, Status: ${result6 === 0 ? "PASS" : "FAIL"}\n`
  );

  // Test Case 7: Duplicate elements
  const arr7: number[] = [1, 2, 3, 2, 4];
  const target7: number = 2;
  const result7: number = linearSearch(arr7, target7);
  console.log(`Test 7 - Array: [${arr7}], Target: ${target7}`);
  console.log(
    `First occurrence - Expected: 1, Got: ${result7}, Status: ${
      result7 === 1 ? "PASS" : "FAIL"
    }`
  );

  // Test Case 8: String elements
  const arr8: string[] = ["apple", "banana", "cherry", "date"];
  const target8: string = "cherry";
  const result8: number = linearSearch(arr8, target8);
  console.log(`Test 8 - Array: [${arr8}], Target: ${target8}`);
  console.log(
    `Expected: 2, Got: ${result8}, Status: ${result8 === 2 ? "PASS" : "FAIL"}\n`
  );

  // Test Case 9: Boolean elements
  const arr9: boolean[] = [true, false, true, false];
  const target9: boolean = false;
  const result9: number = linearSearch(arr9, target9);
  console.log(`Test 9 - Array: [${arr9}], Target: ${target9}`);
  console.log(
    `Expected: 1, Got: ${result9}, Status: ${result9 === 1 ? "PASS" : "FAIL"}\n`
  );

  // Test Case 10: Error handling
  try {
    linearSearch(null as any, 5);
    console.log("Test 10 - Error handling: FAIL (No error thrown)");
  } catch (error) {
    console.log(`Test 10 - Error handling: PASS (${(error as Error).message})`);
  }
}
