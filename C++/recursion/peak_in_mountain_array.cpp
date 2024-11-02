#include <iostream>
#include <vector>
using namespace std;

int findPeak(const vector<int>& arr, int low, int high) {
    int mid = low + (high - low) / 2;
    
    // Check if mid is the peak
    if ((mid == 0 || arr[mid] > arr[mid - 1]) && (mid == arr.size() - 1 || arr[mid] > arr[mid + 1])) {
        return arr[mid];
    }

    // If mid is in the ascending part, move right
    if (mid < arr.size() - 1 && arr[mid] < arr[mid + 1]) {
        return findPeak(arr, mid + 1, high);
    } else {
        // Move left otherwise
        return findPeak(arr, low, mid - 1);
    }
}

int main() {
    vector<int> arr = {1, 3, 8, 12, 4, 2};
    cout << "Peak element: " << findPeak(arr, 0, arr.size() - 1) << endl;
    return 0;
}
