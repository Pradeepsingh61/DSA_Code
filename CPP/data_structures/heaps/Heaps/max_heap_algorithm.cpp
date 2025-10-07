/****************************************
* Max Heap Implementation (Integers)
*
* Description: Implements a Max Heap data structure for integers. 
* Provides efficient access to the maximum element while maintaining 
* the heap property where each parent node is greater than or equal 
* to its children. The heap is stored internally as a dynamic array.
*
* Supported Operations:
* - Build a heap from a given array of integers.
* - Insert a new element while maintaining the max-heap property.
* - Retrieve the maximum element without removing it.
* - Extract (remove) the maximum element from the heap.
* - Delete a specific key from the heap.
* - Print the current elements of the heap.
*
* Time Complexity:
* - buildHeap: O(n)       - heapify applied to all non-leaf nodes
* - insertValue: O(log n) - may traverse up the height of the heap
* - extractMax: O(log n)  - heapify down from root
* - removeKey: O(log n)   - heapify up/down as needed
*
* Space Complexity: O(n) - stores the heap elements in a dynamic array

* Sample Output:

* Max Heap: 15 10 4 5 3 2 

* After inserting 9:
* Max Heap: 15 10 9 5 3 2 4 

* Maximum value: 15

* Extracted max: 15
* After extraction: Max Heap: 10 5 9 4 3 2 

* After removing 5:
* Max Heap: 10 4 9 2 3

* Note:
* - The output shows the heap after each operation, maintaining the max-heap property.
* - Multiple valid heap configurations may exist after insertions or deletions,
*   as long as the max-heap property is preserved.
****************************************/
#include<bits/stdc++.h>
using namespace std;

class MaxHeap {
private:
    vector<int> heapArray;   // Stores heap elements
    int heapSize;            // Current size of the heap
    int heapCapacity;        // Maximum capacity of the heap

    // Function to move an element down the tree to maintain max-heap property
    void heapifyDown(int index) {
        int largest = index;
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;

        if (leftChild < heapSize && heapArray[leftChild] > heapArray[largest])
            largest = leftChild;

        if (rightChild < heapSize && heapArray[rightChild] > heapArray[largest])
            largest = rightChild;

        if (largest != index) {
            swap(heapArray[index], heapArray[largest]);
            heapifyDown(largest);
        }
    }

    // Function to move an element up the tree to maintain max-heap property
    void heapifyUp(int index) {
        while (index > 0 && heapArray[(index - 1) / 2] < heapArray[index]) {
            swap(heapArray[index], heapArray[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }

public:
    // Constructor
    MaxHeap(int capacity) {
        heapSize = 0;
        heapCapacity = capacity;
        heapArray.resize(capacity);
    }

    // Build a max heap from an existing array
    void buildHeap(const vector<int>& input) {
        heapCapacity = input.size();
        heapSize = heapCapacity;
        heapArray = input;

        for (int i = (heapSize - 1) / 2; i >= 0; i--) {
            heapifyDown(i);
        }
    }

    // Insert a new value into the heap
    void insertValue(int value) {
        if (heapSize == heapCapacity) {
            heapCapacity *= 2;
            heapArray.resize(heapCapacity);
        }

        heapArray[heapSize] = value;
        heapSize++;
        heapifyUp(heapSize - 1);
    }

    // Return the maximum value from the heap
    int getMax() const {
        if (heapSize == 0) {
            throw runtime_error("Heap is empty!");
        }
        return heapArray[0];
    }

    // Remove and return the maximum value from the heap
    int extractMax() {
        if (heapSize == 0) {
            throw runtime_error("Heap is empty!");
        }
        if (heapSize == 1) {
            heapSize--;
            return heapArray[0];
        }

        int rootValue = heapArray[0];
        heapArray[0] = heapArray[heapSize - 1];
        heapSize--;
        heapifyDown(0);

        return rootValue;
    }

    // Delete a specific value from the heap
    void removeKey(int key) {
        int index = -1;
        for (int i = 0; i < heapSize; i++) {
            if (heapArray[i] == key) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            cout << "Key not found in heap." << endl;
            return;
        }

        heapArray[index] = heapArray[heapSize - 1];
        heapSize--;

        heapifyDown(index);
        heapifyUp(index);
    }

    // Print all elements in the heap
    void displayHeap() const {
        cout << "Max Heap: ";
        for (int i = 0; i < heapSize; i++) {
            cout << heapArray[i] << " ";
        }
        cout << endl;
    }
};

// Driver Code
int main() {
    MaxHeap maxHeap(6);
    vector<int> values = {2, 3, 4, 5, 10, 15};

    // Build heap from array
    maxHeap.buildHeap(values);
    maxHeap.displayHeap();

    // Insert a new element
    maxHeap.insertValue(9);
    cout << "After inserting 9:" << endl;
    maxHeap.displayHeap();

    // Get max element
    cout << "Maximum value: " << maxHeap.getMax() << endl;

    // Extract max element
    cout << "Extracted max: " << maxHeap.extractMax() << endl;
    cout << "After extraction: ";
    maxHeap.displayHeap();

    // Delete a specific key
    maxHeap.removeKey(5);
    cout << "After removing 5: ";
    maxHeap.displayHeap();

    return 0;
}

