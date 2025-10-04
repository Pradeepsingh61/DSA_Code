#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        int m = heightMap.size(), n = heightMap[0].size();
        vector<vector<int>>vis(m,vector<int>(n,0));
        priority_queue<vector<int>,vector<vector<int>>,greater<>>pq;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(i==0 || i==m-1 || j==0 || j==n-1){
                    pq.push({heightMap[i][j],i,j});
                    vis[i][j]=1;
                }
            }
        }
        int ans = 0;
        vector<vector<int>>del={{0,1},{0,-1},{1,0},{-1,0}};
        while(!pq.empty()){
            int h =pq.top()[0], x=pq.top()[1], y=pq.top()[2]; pq.pop();
            for(int i=0;i<4;i++){
                int nx = x + del[i][0], ny = y + del[i][1];
                if(nx>=0 && nx<m && ny>=0 && ny<n && !vis[nx][ny]){
                    ans+=max(0, h - heightMap[nx][ny]);
                    pq.push({max(h,heightMap[nx][ny]),nx,ny});
                    vis[nx][ny]=1;
                }
            }
        }
        return ans;
    }
};