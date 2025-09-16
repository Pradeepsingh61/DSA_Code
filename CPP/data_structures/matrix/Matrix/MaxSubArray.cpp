#include <iostream>
#include <vector>
#include <climits>
using namespace std;
int KedansAlgo(vector<int> nums, int n)
{
    int ans = INT_MIN;
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += nums[i];
        ans = max(ans, sum);        // if the now sum is bigger than the ans update it 
        if (sum < 0)                // if sum is negative than start i new subarray from that poisition
            sum = 0;                // and set the sum = 0
    }
    return ans;
}
int BruteFroce(vector<int> arr, int n)
{
    int ans = INT_MIN;
    for (int i = 0; i < n; i++) // traversing the entire array
    {
        int sum = 0;
        for (int j = i; j < n; j++) // traverse the array from a position to the end of the array
        {
            sum += arr[j];
            ans = max(sum ,ans);
        }
    }
    return ans;
}
int main()
{
    vector<int> arr = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int n = arr.size();
    int Max = KedansAlgo(arr, n);
    cout << "**The Maximum sum of Subaaray is**" << endl;
    cout << endl << "By KEDAN's Algorithms : " << Max << endl;
    Max = BruteFroce(arr, n);
    cout << "By Basic Code : " << Max << endl;
    return 0;
}