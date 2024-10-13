class Solution {
public:

    bool Solve(string &s, string &p,int i,int j,vector<vector<int>>&dp){
               if (i == s.size() && j == p.size()) {
            return true; // Both strings are fully traversed
        }
        if (j >= p.size()) {
            return false; // Pattern is exhausted but string is not
        }

        if (i >= s.size()) {
            while (j < p.size()) {
                if (p[j] != '*') return false; // Only '*' can match an empty string
                j++;
            }
            return true;
        }
        if (dp[i][j] != -1) return dp[i][j];
        if (s[i] == p[j] || p[j] == '?') {
            return dp[i][j]= Solve(s, p, i + 1, j + 1,dp); // Match current character or '?'
        } else if (p[j] == '*') {
          return  dp[i][j]=( Solve(s, p, i + 1, j,dp) || Solve(s, p, i, j + 1,dp)); // '*' matches 0 or more characters
        }
        return dp[i][j]= false;
    }

    bool isMatch(string s, string p) {
        vector<vector<int>>dp(s.size()+1,vector<int>(p.size()+1,-1));
        return Solve(s,p,0,0,dp);
    }
};
