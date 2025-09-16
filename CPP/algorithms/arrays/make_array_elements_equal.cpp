/*
Make all array elements equal with minimum cost
*/

/*
Input  : arr[] = [1, 100, 101]
Output : 100
We can change all its values to 100 with minimum cost,
|1 - 100| + |100 - 100| + |101 - 100| = 100
Input  : arr[] = [4, 6]
Output : 2
We can change all its values to 5 with minimum cost,
|4 - 5| + |5 - 6| = 2
*/

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
#include <cmath>
#include <algorithm>
#include <climits>

using namespace std;

void makingEqual(vector<int> &arr)
{
    int min = INT_MAX;
    int max = INT_MIN;
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i] < min)
        {
            min = arr[i];
        }
    }
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    int sum = 0;
    for (int i = min; i < max; i++)
    {
        sum += arr[i] - i;
        if (sum == i)
        {
            cout << sum << endl;
        }
        else
        {
            continue;
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
    vector<int> arr = {1, 100, 101};
    vector<int> arr2 = {2, 3, 8, 3, 13};

    cout << "arr: ";
    print_vector(arr);
    cout << "arr2: ";
    print_vector(arr2);

    makingEqual(arr);
    makingEqual(arr2);
    return 0;
}