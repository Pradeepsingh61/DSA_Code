class Solution {
public:
bool checkpalindrom(string a,int i,int j){
    while(i<=j){
        if(a[i]!=a[j]){
            return 0;
        }
        i++;
        j--;
    }
    return 1;
}
    bool validPalindrome(string s) {
        int i=0;
        int j=s.size()-1;
        while(i<=j){
            if(s[i]!=s[j]){
                return checkpalindrom(s,i+1,j)||checkpalindrom(s,i,j-1);
            }
            else{
                i++;
                j--;
            }
        }
        return true;
    }
};
