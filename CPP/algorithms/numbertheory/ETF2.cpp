// ɸ(n) = n  *  ((P₁-1)/P₁) X ((P₂-1)/P₂) ... X ((Pₖ-1)/Pₖ)

#include<bits/stdc++.h>
#define raj_01 ios::sync_with_stdio(false);cin.tie(0);
#define speed1 cin.tie(0);
#define speed2 cout.tie(0);
#define print(val) cout << val << endl;
#define for1(i,n) for(int i = 0; i < n ; i++)
#define fork(i,n,k) for(int i = 0; i < n ; i+=k)
#define printcontainer(i,container) for1(i,container.size()) print(container[i])
#define INF 1e18
#define INIT_MATRIX(rows, cols, value) \
int matrix[rows][cols];            \
for (int i = 0; i < rows; ++i)     \
for (int j = 0; j < cols; ++j) \
cin >> matrix[i][j]
#define MOD 1000000007
#define ll long long
#define lli long long int
#define vi vector<int>
#define pii pair<int, int>
#define vvi vector<vi>
#define all(x) (x).begin(), (x).end() 
#define endl "\n"
#define debug(x) cout << #x << " = " << x << endl
#define debug2(x, y) cout << #x << " = " << x << #y << " = " << y << endl
#define debug3(x, y, z) cout << #x << " = " << x << #y << " = " << y << int << #z << " = " << z << endl
using namespace std;

int phi(int n) {
    int res = n;
    for(int i = 2 ; i * i <= n ; i++) {
        if(n%i==0) {
            res /= i;
            res *= (i-1);
            while(n%i==0) n/=i;
        }
    }
    if(n>1) {
        res /= n;
        res *= (n-1);
    }
    return res;
}

int main(){
    raj_01
    int test,n;
    cin >> test;
    while(test--) {
        cin >> n;
        cout << phi(n) << endl;
    }
    return 0;
}