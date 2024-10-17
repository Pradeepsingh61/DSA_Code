//code link https://leetcode.com/problems/largest-rectangle-in-histogram/

#include<bits/stdc++.h>
using namespace std;

//this problem demonstrates the best implementation of the stack
class Solution {
public:
    int largestRectangleArea(vector<int>& height) {
        int n=height.size();
vector<int>right(n,n);
vector<int>left(n,-1);
stack<int>st;
//for Next samllest right(NSR)
for(int i=0;i<n;i++){
    while(!st.empty()&& height[st.top()]>height[i]){
        right[st.top()]=i;
        st.pop();
    }
    st.push(i);
}

//for Next smallest left(NSL)
for(int i=n-1;i>=0;i--){
    while(!st.empty() && height[st.top()]>height[i]){
        left[st.top()]=i;
        st.pop();
    }
    st.push(i);
}
int ans=0;
// maximum height for the given index is the (NSR-NSL-1)
for(int i=0;i<n;i++){
    ans=max(ans,height[i]*(right[i]-left[i]-1));
}
return ans;
}

};