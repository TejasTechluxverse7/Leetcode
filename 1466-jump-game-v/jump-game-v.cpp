class Solution {
public:
    int n, d;
    vector<int> dp;

    int dfs(int i, vector<int>& arr) {
        if (dp[i] != -1) return dp[i];

        int best = 1; // start at i itself

        // Check left side
        for (int j = i - 1; j >= max(0, i - d); --j) {
            if (arr[j] >= arr[i]) break;   // blocked
            best = max(best, 1 + dfs(j, arr));
        }

        // Check right side
        for (int j = i + 1; j <= min(n - 1, i + d); ++j) {
            if (arr[j] >= arr[i]) break;   // blocked
            best = max(best, 1 + dfs(j, arr));
        }

        return dp[i] = best;
    }

    int maxJumps(vector<int>& arr, int d) {
        n = arr.size();
        this->d = d;
        dp.assign(n, -1);

        int ans = 1;
        for (int i = 0; i < n; ++i) {
            ans = max(ans, dfs(i, arr));
        }
        return ans;
    }
};