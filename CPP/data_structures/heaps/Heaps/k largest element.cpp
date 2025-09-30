#include <bits/stdc++.h>
using namespace std;

/*
Problem: Find the K largest elements in an array using a Min-Heap.

Algorithm:
1. Initialize a min-heap (priority_queue with greater<int>) of size k.
2. Push the first k elements into the heap.
3. For each remaining element:
   - If it is larger than the heap top, replace the heap top with this element.
4. Extract elements from the heap for final result.
5. Optionally, sort result in descending order.
*/

class Solution {
public:
    vector<int> kLargestElements(vector<int>& arr, int k) {
        // Min-heap to keep track of k largest elements
        priority_queue<int, vector<int>, greater<int>> minHeap;

        // Step 1: Add first k elements to heap
        for(int i = 0; i < arr.size(); i++) {
            if(minHeap.size() < k) {
                minHeap.push(arr[i]); // Fill heap until size k
            } 
            // Step 2: Maintain heap with largest k elements
            else if(arr[i] > minHeap.top()) {
                minHeap.pop();        // Remove smallest in heap
                minHeap.push(arr[i]); // Add current element
            }
        }

        // Step 3: Extract elements from heap into result vector
        vector<int> result;
        while(!minHeap.empty()) {
            result.push_back(minHeap.top());
            minHeap.pop();
        }

        // Step 4: Sort in descending order for clarity
        sort(result.rbegin(), result.rend());

        return result;
    }
};

// Driver code to test the Solution class
int main() {
    Solution sol;
    vector<int> arr = {5, 12, 11, -1, 12};
    int k = 3;

    vector<int> largest = sol.kLargestElements(arr, k);

    cout << "The " << k << " largest elements are: ";
    for(int num : largest)
        cout << num << " ";
    cout << endl;

    return 0;
}
