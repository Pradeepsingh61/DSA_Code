/*
 Given a stack with push(), pop(), and empty() operations, The task is to delete the middle element of it without using any additional data structure.


    Input  : Stack[] = [1, 2, 3, 4, 5]
    Output : Stack[] = [1, 2, 4, 5]

    Input  : Stack[] = [1, 2, 3, 4, 5, 6]
    Output : Stack[] = [1, 2, 4, 5, 6]

 */

#include <iostream>
#include<bits/stdc++.h>
using namespace std;
 
int main() {
    stack<char> st;
    st.push('1');
    st.push('2');
    st.push('3');
    st.push('4');
    st.push('5');
    st.push('6');
    st.push('7');
    vector<char>v;
    while(!st.empty()){
      v.push_back(st.top());
      st.pop();
    }
    int n=v.size();
    if(n%2==0){
      int target=(n/2);
      for(int i=0;i<n;i++){
        if(i==target)continue;
        st.push(v[i]);
      }
    }else{
      int target=ceil(n/2); 
      for(int i=0;i<n;i++){
        if(i==target)continue;
        st.push(v[i]);
      }
    }
    cout<<"Printing stack after deletion of middle: "; 
    while (!st.empty()) {
        char p = st.top();
        st.pop();
        cout << p << " ";
    }
    return 0;
}

