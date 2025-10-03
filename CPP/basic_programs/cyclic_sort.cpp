#include <iostream>
#include <vector>
using namespace std;

void cyclicSort(vector<int>& nums) {
    int i = 0;
    int n = nums.size();
    while (i < n) {
        int correctIndex = nums[i] - 1;
        if (nums[i] >= 1 && nums[i] <= n && nums[i] != nums[correctIndex]) {
            swap(nums[i], nums[correctIndex]);
        } else {
            i++;
        }
    }
}

void print(vector<int>& nums){
    cout<<"Sorted array is:"<<endl;

    for(auto i:nums){
        cout<<i<<" "<<endl;
    }
}
int main() {
    cout<<"This is cyclic sort code. Cyclic sort works from 1 to n or 0 to n-1 without duplicates."<<endl;
    int n;
    cout<<"Enter value of n"<<endl;
    cin>>n;
    vector<int> nums(n,0);
    for(int i=0;i<n;i++)
    cin>>nums[i];
    cyclicSort(nums);
    print(nums);
    return 0;
}
