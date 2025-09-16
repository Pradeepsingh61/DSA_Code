/*
Find duplicates in O(n) time and O(1) extra space
*/
/*
Input: n=7 , array[]={1, 2, 3, 6, 3, 6, 1}
Output: 1, 3, 6
*/
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

void duplicate(vector<int> &arr)
{
    map<int, int> duplicates;
    for (int i = 0; i < arr.size(); i++)
    {
        duplicates[arr[i]]++;
    }
    for (const auto &it : duplicates)
    {
        if (it.second > 1)
        {
            cout << it.first << " ";
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
    vector<int> arr = {2, 1, 5, 4, 1, 3, 5};
    vector<int> arr2 = {2, 3, 8, 3, 13};

    cout << "arr: ";
    print_vector(arr);
    cout << "arr2: ";
    print_vector(arr2);

    duplicate(arr);
    return 0;
}