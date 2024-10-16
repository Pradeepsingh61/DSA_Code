/*
Count Inversions
*/

/*
Given an array of integers. Find the Inversion Count in the array.
Two elements arr[i] and arr[j] form an inversion if arr[i] > arr[j] and i < j.

Inversion Count: For an array, inversion count indicates how far (or close) the array is from being sorted. If the array is already sorted then the inversion count is 0.
If an array is sorted in the reverse order then the inversion count is the maximum.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void countInversion(vector<int> &arr)
{
    int inversionCount = 0;
    for (int i = 0; i < arr.size() - 1; i++)
    {
        for (int j = i + 1; j < arr.size(); j++)
        {
            if (arr[i] > arr[j] && i < j)
            {
                inversionCount++;
            }
        }
    }
    cout << "Inversion Count: " << inversionCount << endl;
}

void print_vector(const vector<int> &vec)
{
    for (int num : vec)
    {
        cout << num << " ";
    }
    cout << std::endl;
}

int main()
{
    vector<int> arr = {2, 4, 1, 3, 5};
    vector<int> arr2 = {2, 3, 8, 13};

    cout << "arr: ";
    print_vector(arr);
    cout << "arr2: ";
    print_vector(arr2);

    countInversion(arr);
    return 0;
}