class Solution {
public:
    int maxPathScore(vector<vector<int>>& g, int k) {
        int m=g.size(),n=g[0].size();
        vector dp(m,vector(n,vector<int>(k+1,-1)));
        dp[0][0][0]=0;
        
        for(int i=0;i<m;i++)for(int j=0;j<n;j++)
            for(int c=0;c<=k;c++) if(dp[i][j][c]!=-1){
                if(i+1<m){
                    int nc=c+(g[i+1][j]>0), ns=dp[i][j][c]+g[i+1][j];
                    if(nc<=k) dp[i+1][j][nc]=max(dp[i+1][j][nc],ns);
                }
                if(j+1<n){
                    int nc=c+(g[i][j+1]>0), ns=dp[i][j][c]+g[i][j+1];
                    if(nc<=k) dp[i][j+1][nc]=max(dp[i][j+1][nc],ns);
                }
            }
        
        return *max_element(dp[m-1][n-1].begin(),dp[m-1][n-1].end());
    }
};