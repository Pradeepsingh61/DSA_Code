/*
  Priority Queue Implementation using Max-Heap in C
  -------------------------------------------------
  A Priority Queue is a data structure where each element has a priority,
  and the element with the highest priority is served before others.

  Here, we use a binary Max-Heap representation:
  - Insertion maintains heap order by heapifying up.
  - Deletion of root (highest priority element) is handled by replacing it 
    with the last element and heapifying down.

  Time Complexity:
    - Insertion: O(log n)
    - Deletion: O(log n)
    - Heapify: O(log n)
    - Printing: O(n)

  Space Complexity:
    - O(n), where n is the number of elements in the heap.
*/

#include <stdio.h>

int heapSize = 0;  // Global variable to track current heap size

// Utility function to swap two elements
void swap(int *a, int *b) {
  int temp = *b;
  *b = *a;
  *a = temp;
}

/*
  Heapify function:
  Ensures the max-heap property at index 'i' assuming subtrees are already heaps.
  - Compares node with left and right children.
  - If any child is larger, swap and continue heapifying down.
*/
void heapify(int heapArray[], int heapSize, int index) {
  if (heapSize == 1) {
    printf("Single element in the heap\n");
    return;
  }

  int largest = index;              // Initialize largest as root
  int leftChild = 2 * index + 1;    // Left child index
  int rightChild = 2 * index + 2;   // Right child index

  // Compare left child with root
  if (leftChild < heapSize && heapArray[leftChild] > heapArray[largest])
    largest = leftChild;

  // Compare right child with current largest
  if (rightChild < heapSize && heapArray[rightChild] > heapArray[largest])
    largest = rightChild;

  // If root is not largest, swap with largest and recurse
  if (largest != index) {
    swap(&heapArray[index], &heapArray[largest]);
    heapify(heapArray, heapSize, largest);
  }
}

/*
  Insert function:
  Inserts a new element into the heap and restores max-heap property.
  - Add new element at the end.
  - Call heapify from bottom-up to restore heap.
*/
void insert(int heapArray[], int newElement) {
  if (heapSize == 0) {
    heapArray[0] = newElement;
    heapSize += 1;
  } else {
    heapArray[heapSize] = newElement;
    heapSize += 1;

    // Re-heapify the tree
    for (int i = heapSize / 2 - 1; i >= 0; i--) {
      heapify(heapArray, heapSize, i);
    }
  }
}

/*
  Delete function:
  Deletes the element 'elementToDelete' from the heap.
  - Find the element.
  - Replace it with the last element.
  - Reduce heap size and restore max-heap property.
*/
void deleteRoot(int heapArray[], int elementToDelete) {
  int i;
  for (i = 0; i < heapSize; i++) {
    if (elementToDelete == heapArray[i])
      break;
  }

  // Swap with last element and reduce heap size
  swap(&heapArray[i], &heapArray[heapSize - 1]);
  heapSize -= 1;

  // Re-heapify the tree
  for (int i = heapSize / 2 - 1; i >= 0; i--) {
    heapify(heapArray, heapSize, i);
  }
}

/*
  Print function:
  Prints all elements of the heap array.
  Complexity: O(n)
*/
void printHeap(int heapArray[], int heapSize) {
  for (int i = 0; i < heapSize; ++i)
    printf("%d ", heapArray[i]);
  printf("\n");
}

// Driver code to test Priority Queue implementation
int main() {
  int heapArray[10];  // Fixed-size array for heap

  // Insert elements
  insert(heapArray, 3);
  insert(heapArray, 4);
  insert(heapArray, 9);
  insert(heapArray, 5);
  insert(heapArray, 2);

  printf("Max-Heap array: ");
  printHeap(heapArray, heapSize);

  // Delete an element
  deleteRoot(heapArray, 4);

  printf("After deleting element 4: ");
  printHeap(heapArray, heapSize);

  return 0;
}
