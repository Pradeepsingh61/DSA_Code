#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> zFunction(string s) {
    int n = s.length();
    vector<int> z(n);
    int l = 0, r = 0;

    for (int i = 1; i < n; i++) {
        if (i <= r) {
            int k = i - l;
            
            // Case 2: reuse the previously computed value
            z[i] = min(r - i + 1, z[k]);
        }

        // Try to extend the Z-box beyond r
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }

        // Update the [l, r] window if extended
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }

    return z;
}

int main(){
    string s = "aabxaab";
    
    vector<int> z = zFunction(s);
    
    for(int i=0; i < z.size(); ++i){
        cout<<z[i]<<" ";
    }

    // ALGO INFO

    cout<<endl<<endl;
    cout<<"=================\n";
    cout<<" ALGORITHM INFO \n";
    cout<<"=================\n\n";
    cout<<"Time COmplexity : O(n)\n";
    cout<<"Space Complexity : O(n)\n";
    return 0;
}
