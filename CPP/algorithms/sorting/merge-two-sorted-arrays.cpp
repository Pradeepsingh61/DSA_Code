/*
Merge two sorted arrays with O(1) extra space
*/

/*
nput: a[] = {10}, b[] = {2, 3}
Output: a[] = {2}, b[] = {3, 10}

Input: a[] = {1, 5, 9, 10, 15, 20}, b[] = {2, 3, 8, 13}
Output: a[] = {1, 2, 3, 5, 8, 9}, b[] = {10, 13, 15, 20}
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void merge_array(vector<int> &arr, vector<int> &arr2)
{
    // for (int &num : arr2)
    // { // arr2.size()
    //     for (int &num1 : arr)
    //     {
    //         if (num < num1)
    //         { // if arr2 element is smaller than arr element
    //             swap(num1, num);

    //             break; // swap and break the loop
    //         }
    //     }
    // }

    for (int k = 0; k < arr2.size(); k++)
    {
        for (int i = 0; i < arr2.size(); i++)
        {
            for (int j = 0; j < arr.size(); j++)
            {
                cout << arr2[i] << "  " << arr[j] << endl;
                if (arr2[i] < arr[j])
                {
                    swap(arr2[i], arr[j]);
                    break;
                }
            }
        }
    }
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
    vector<int> arr = {1, 5, 9, 10, 15, 20};
    vector<int> arr2 = {2, 3, 8, 13};

    cout << "Before merging:" << endl;
    cout << "arr: ";
    print_vector(arr);
    cout << "arr2: ";
    print_vector(arr2);

    merge_array(arr, arr2);

    cout << "After merging:" << endl;
    cout << "arr: ";
    print_vector(arr);
    cout << "arr2: ";
    print_vector(arr2);
    return 0;
}