class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& w) {
        int n=s.size(), m=w.size(), len=w[0].size(), total=m*len;
        unordered_map<string,int> mp;
        for(auto &x:w) mp[x]++;
        
        vector<int> ans;
        for(int i=0;i<len;i++){
            unordered_map<string,int> seen;
            int l=i, count=0;
            
            for(int r=i;r+len<=n;r+=len){
                string t=s.substr(r,len);
                if(mp.count(t)){
                    seen[t]++, count++;
                    while(seen[t]>mp[t]){
                        seen[s.substr(l,len)]--, l+=len, count--;
                    }
                    if(count==m) ans.push_back(l);
                } else {
                    seen.clear(), count=0, l=r+len;
                }
            }
        }
        return ans;
    }
};