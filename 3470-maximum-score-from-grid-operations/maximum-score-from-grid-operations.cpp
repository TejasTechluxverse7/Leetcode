class Solution {
public:
    long long maximumScore(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<long long>> colSum(n, vector<long long>(n + 1, 0));
        
        for (int c = 0; c < n; ++c) {
            for (int r = 0; r < n; ++r) {
                colSum[c][r + 1] = colSum[c][r] + grid[r][c];
            }
        }

        vector<vector<long long>> prev_dp(n + 1, vector<long long>(n + 1, 0));
        for (int curr = 0; curr <= n; ++curr) {
            for (int nxt = 0; nxt <= n; ++nxt) {
                if (nxt > curr) {
                    prev_dp[curr][nxt] = colSum[0][nxt] - colSum[0][curr];
                }
            }
        }

        for (int c = 1; c < n; ++c) {
            vector<vector<long long>> curr_dp(n + 1, vector<long long>(n + 1, 0));
            for (int curr = 0; curr <= n; ++curr) {
                vector<long long> pref_max(n + 1, 0);
                pref_max[0] = prev_dp[0][curr];
                for (int i = 1; i <= n; ++i) {
                    pref_max[i] = max(pref_max[i - 1], prev_dp[i][curr]);
                }

                vector<long long> suff_max(n + 2, 0);
                for (int i = n; i >= 0; --i) {
                    long long s = (i > curr) ? colSum[c][i] - colSum[c][curr] : 0;
                    suff_max[i] = max(suff_max[i + 1], prev_dp[i][curr] + s);
                }

                for (int nxt = 0; nxt <= n; ++nxt) {
                    long long s_next = (nxt > curr) ? colSum[c][nxt] - colSum[c][curr] : 0;
                    curr_dp[curr][nxt] = max(pref_max[nxt] + s_next, suff_max[nxt + 1]);
                }
            }
            prev_dp = curr_dp;
        }

        long long ans = 0;
        for (int curr = 0; curr <= n; ++curr) {
            ans = max(ans, prev_dp[curr][0]);
        }
        return ans;
    }
};