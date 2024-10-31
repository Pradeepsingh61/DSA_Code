#include <iostream>
#include <vector>
using namespace std;

int findPivot(const vector<int>& arr, int low, int high) {
    // Base case: if only one element left, it's the pivot
    if (low == high) {
        return low;
    }
    
    int mid = low + (high - low) / 2;
    
    // Check if mid is the pivot
    if (mid < high && arr[mid] > arr[mid + 1]) {
        return mid + 1;
    }
    if (mid > low && arr[mid] < arr[mid - 1]) {
        return mid;
    }

    // Decide to search in the left or right half
    if (arr[low] >= arr[mid]) {
        return findPivot(arr, low, mid - 1);
    } else {
        return findPivot(arr, mid + 1, high);
    }
}

int main() {
    vector<int> arr = {4, 5, 6, 7, 0, 1, 2};
    int pivotIndex = findPivot(arr, 0, arr.size() - 1);
    cout << "Pivot element: " << arr[pivotIndex] << " at index " << pivotIndex << endl;
    return 0;
}
