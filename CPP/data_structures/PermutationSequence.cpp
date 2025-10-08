class Solution {
private:
void solve(string str,int index,vector<string>&ans)
{
    if(index>=str.size())
    {
        ans.push_back(str);
        return;
    }
    for(int i=index;i<str.size();i++)
    {
        swap(str[i],str[index]);
        solve(str,index+1,ans);
    }
}
public:
    string getPermutation(int n, int k) 
    {
        string str="";
        char digit='1';
        while(n--)
        {
            str+=digit;
            digit++;
        }
        vector<string>ans;
        solve(str,0,ans);
        return ans[k-1];
    }
};
