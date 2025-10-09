class Solution {
public:
    vector<vector<int>> dirs = {{0,-1},{0,1},{-1,0},{1,0}};
    
    bool dfs(int x, int y, int t, vector<vector<int>>& grid, vector<vector<bool>>& vis) {
        int n = grid.size();
        vis[x][y] = true;
        if (x == n - 1 && y == n - 1) return true;
        
        for (auto& d : dirs) {
            int nx = x + d[0], ny = y + d[1];
            if (nx >= 0 && nx < n && ny >= 0 && ny < n && !vis[nx][ny] && grid[nx][ny] <= t) {
                if (dfs(nx, ny, t, grid, vis)) return true;
            }
        }
        return false;
    }
    
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        int low = 0, high = n * n - 1, ans = INT_MAX;

        while (low <= high) {
            int mid = (low + high) / 2;
            vector<vector<bool>> vis(n, vector<bool>(n, false));
            if (grid[0][0] <= mid && dfs(0, 0, mid, grid, vis)) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return ans;
    }
};
