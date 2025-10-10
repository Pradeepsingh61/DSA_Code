// problem to be solved is 

// ans  = Σ (1 to N) gcd(i , N)   // for q queries


// observation one = GCD(i,N) = one of the divisors of N

// Assume N = 12

// gcd(1,12) = 1
// gcd(2,12) =  2
// gcd(3,12) = 3
// gcd(4,12) = 4
// gcd(5,12) = 1
// gcd(6,12) = 6
// gcd(7,12) = 1
// gcd(8,12) = 4
// gcd(9,12) = 3
// gcd(10,12) = 2
// gcd(11,12) = 1
// gcd(12,12)  12

// sum of gcds =   1 + 2 + 3 + 4 + 1 + 6 +1 + 4 +3 +2 + 1 +12

// sum of gcds  = 1*4 + 2*2 + 3*2 + 4*2 + 12*1

// we can say that 

// sum of gcd = (for divisor 1 * how many nymber are from 1 to 12 have gcd equal divisor(1))


// like for divisor 2 , how many numbers from 1 to 12 have gcd 2 that will be the contibution  of gcd 2 with that count of numbers

// this is the way to calculate gcd sum

// for x1 , x2 , ...xm for a divisor d such that gcd(xi , N) = d

// have to find m (count)

// gcd(xi/d , N/d) = 1;

// means how many xi/d are there in 1 to N such that their gcd with N/D is 1

// 1 means co prime ==> co prime count ==> ETF(N/d) that is the answer

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

int getCount(int d , int N) {
    return ETF[N/d];
}


int main(){
    raj_01
    init();
    int t , N;
    cin >> t;
    while(t--){
        cin >> N;
        int res = 0;
        for(int i = 1 ; i*i<=N ; i++) {
            if(N%i==0) {
                int d1 = i , d2 = N/i;
                res += (d1*getCount(d1,N));
                if(d1 != d2) res += (d2*getCount(d2,N));
            }
        } // sqrt(n) = TC(O )
        cout << res << endl;
    }
    return 0;
}


