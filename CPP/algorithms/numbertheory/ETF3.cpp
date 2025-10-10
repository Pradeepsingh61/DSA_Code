// efficient way to calculate all etf values from 1 to 10⁶


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

int ETF[1000001];

void init() {
    ETF[0] = -1; // not defined for 0
    for(int i = 1 ; i < 1000001 ; i++) ETF[i] = i;

    for(int i = 2 ; i  < 1000001 ; i++) {
        if(ETF[i] == i) {
            for(int j = i ; j < 1000001 ;j += i) {
                ETF[j] /= i;
                ETF[j] *= (i-1);
            }
        } 
    }
}
int main(){
    raj_01
    init();
    int t,n;
    cin >> t;
    while(t--) {
        cin >> n , cout << ETF[n] << endl;
    }
    return 0;
}