class Solution {
public:
    unordered_map<string_view, int> freq;
    inline void toFreq(string& s){
        string_view sv(s);
        const int n=sv.size();
        for (int l=0, r=0; r<= n; r++) {
            if (r==n || sv[r]==' ') {  // Word boundary
                if (r>l) {
                    string_view word = sv.substr(l, r-l);
                    freq[word]++;
                }
                l=r+1;  // Move to the next word
            }
        }  
    }
    vector<string> uncommonFromSentences(string& s1, string& s2) {
        freq.reserve(200);
        toFreq(s1);
        toFreq(s2);
        vector<string> ans;
        for(auto& [s, f]: freq){
            if(f==1) ans.emplace_back(s);
        }
        return ans;
    }
};
