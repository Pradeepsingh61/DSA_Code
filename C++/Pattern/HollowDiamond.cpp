// ---*
// --*-*
// -*---*
// *-----*
// *-----* //i=4 j=1 //i=4 j=7
// -*---* // i=5 j=2 //i=5 j=6
// --*-*  // i=6 j=3 //i=6 j=5
// ---*
#include <iostream>
using namespace std;
int main(){
    int n;
    cin>>n;
    for(int i=0;i<2*n;i++){
        if(i<n){
            for(int sp=n-i-1;sp>=0;sp--){
            cout<<" ";
            }
            for(int j=0;j<2*i+1;j++){
                if(j==0 || j==2*i){
                cout<<"*";
                }else {
                    cout<<" ";
                }   
            }
            cout<<endl;
            }
            else if (i>=n){
                for(int sp=i;sp>=0;sp--){
                    cout<<" ";
                }
                for(int j=0;j<2*n-2*i-1;j++){
                    if(j==0 ||j==2*n-2*i-2){
                        cout<<"*";
                    } else{
                        cout<<" ";
                    }
                }
                cout<<endl;
            }
    }
}