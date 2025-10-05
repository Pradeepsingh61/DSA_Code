class Solution {
  public:
    void pushing(int x, int y, vector<vector<int>> &v,string temp, vector<string> &ans, vector<vector<int>> &vis) {
    int n = v.size();
    if (x == n-1 && y == n-1) {
        ans.push_back(temp);
        return;

    }
    if (y+1<n && v[x][y+1] && vis[x][y+1] == 0) {
        vis[x][y+1] = 1;
        temp += "R";
        pushing(x,y+1,v,temp,ans,vis);
        temp.pop_back();
        vis[x][y+1] = 0;

    }
    if (y-1>=0 && v[x][y-1] && vis[x][y-1] == 0) {
        vis[x][y-1] = 1;
        temp += "L";
        pushing(x,y-1,v,temp,ans,vis);
        temp.pop_back();
        vis[x][y-1] = 0;

    }
    if (x+1<n && v[x+1][y] && vis[x+1][y] == 0) {
        vis[x+1][y] = 1;
        temp += "D";
        pushing(x+1,y,v,temp,ans,vis);
        temp.pop_back();
        vis[x+1][y] = 0;

    }
    if (x-1>=0 && v[x-1][y] && vis[x-1][y] == 0) {
        vis[x-1][y] = 1;
        temp += "U";
        pushing(x-1,y,v,temp,ans,vis);
        temp.pop_back();
        vis[x-1][y] = 0;

    }
    return;

    }
    vector<string> ratInMaze(vector<vector<int>>& maze) {
        int n = maze.size();
        string ans = "";
        vector<string> v;
        vector<vector<int>> vis(n,vector<int>(n,0));
        vis[0][0] = 1;
        pushing(0,0,maze,ans,v,vis);
        sort(v.begin(),v.end());
        return v;

    }
};
