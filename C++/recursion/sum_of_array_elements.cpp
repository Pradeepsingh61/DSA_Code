#include <iostream>
#include <vector>

using namespace std;

// Recursive function to calculate sum of n elements
int sumOfElements(const vector<int>& arr, int n) {
    // Base case: If n is 0, sum is 0
    if (n == 0) {
        return 0;
    }

    // Recursive case: Sum of n elements is the nth element plus the sum of the first n-1 elements
    return arr[n - 1] + sumOfElements(arr, n - 1);
}

int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter the elements: ";
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    // Call the recursive function and output the result
    int sum = sumOfElements(arr, n);
    cout << "Sum of elements: " << sum << endl;

    return 0;
}
