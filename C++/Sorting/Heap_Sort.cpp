// C++ program for implementation of Heap Sort using vector
#include <bits/stdc++.h>
using namespace std;

// Heapify method which create the max heap in O(n) cpmplexity
void heapify(vector<int>& arr, int n, int i){
    // Initialize largest as root
    int largest = i;

    // left index = 2*i + 1
    int l = 2 * i + 1;

    // right index = 2*i + 2
    int r = 2 * i + 2;

    // If left child is larger than root
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);

        heapify(arr, n, largest);
    }
}

// Main function to do heap sort
void heapSort(vector<int>& arr){
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        swap(arr[0], arr[i]);

        heapify(arr, i, 0);
    }
}

int main(){
    vector<int> arr = { 9, 4, 3, 8, 10, 2, 5 };

    heapSort(arr);

    cout << "Sorted array is: ";
    for (int i = 0; i < arr.size(); ++i)
        cout << arr[i] << " ";
}
