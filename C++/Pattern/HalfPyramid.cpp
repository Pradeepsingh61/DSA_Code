// *
// **
// ***
// ****


#include <iostream>
using namespace std;
int main(){
    // this is a code for half pyramid pattern and here the n represents number of lines of traversal;
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=0;j<i;j++){
            cout<<"*";
        }
        cout<<endl;
    }

}