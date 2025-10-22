/* Insertion Sort

Description:
Insertion Sort builds the final sorted array one element at a time.
It iterates through the array, taking the current element and inserting it into its correct
position among the already sorted elements to its left.

Time Complexity: 
- Best Case: O(n) - Already sorted array
- Average Case: O(n²)
- Worst Case: O(n²)

Space Complexity: O(1) - In-place Algorithm
*/


function insertionSort(arr){
    const n=arr.length;

    for(let i=1;i<n;i++){
        let j=i;

        //shift elements greater than arr[j] one position ahead
        while(j>0 && arr[j-1]>arr[j]){
            //swap using destructuring
            [arr[j-1], arr[j]]=[arr[j], arr[j-1]];
            j--;
        }
    }

    return arr;
}

function runTests(){
    console.log("Insertion Sort Test cases:");

    //Test 1: Regular unsorted array
    const test1=[64, 34, 25, 12, 22, 11, 90];
    console.log("\nTest 1 - Original: ", test1);
    console.log("Test 1 - Sorted: ", insertionSort(test1));

    //Test2: Already sorted array
    const test2=[1, 2, 3, 4, 5];
    console.log("\nTest 2 - Original: ", test2);
    console.log("Test 2 - Sorted", insertionSort(test2));

    //Test 3: Reverse sorted array
    const test3=[5, 4, 3, 2, 1];
    console.log("\nTest 3 - Original: ", test3);
    console.log("Test 3 - Sorted: ", insertionSort(test3));

    //Test 4: Array with duplicates
    const test4=[3, 1, 4, 1, 5, 9, 2, 6, 5];
    console.log("\nTest4 - Original: ", test4);
    console.log("Test 4 - Sorted: ", insertionSort(test4));

    //Test 5: Single element array
    const test5=[27];
    console.log("\nTest 5 - Original: ", test5);
    console.log("Test 5 - Sorted: ", insertionSort(test5));

    //Test 6: Empty array
    const test6=[];
    console.log("\nTest 6 - Original: ", test6);
    console.log("Test 6 - Sorted: ", insertionSort(test6));

}

runTests();