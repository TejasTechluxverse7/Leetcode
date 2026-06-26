class Solution {
public:
    unordered_map<string, bool> dp;

    bool solve(string a, string b) {
        if (a == b) return true;

        string key = a + "#" + b;
        if (dp.count(key)) return dp[key];

        int n = a.size();

        // Prune using character frequency
        vector<int> cnt(26, 0);
        for (int i = 0; i < n; i++) {
            cnt[a[i] - 'a']++;
            cnt[b[i] - 'a']--;
        }
        for (int x : cnt) {
            if (x != 0)
                return dp[key] = false;
        }

        for (int i = 1; i < n; i++) {
            // Without swap
            if (solve(a.substr(0, i), b.substr(0, i)) &&
                solve(a.substr(i), b.substr(i)))
                return dp[key] = true;

            // With swap
            if (solve(a.substr(0, i), b.substr(n - i)) &&
                solve(a.substr(i), b.substr(0, n - i)))
                return dp[key] = true;
        }

        return dp[key] = false;
    }

    bool isScramble(string s1, string s2) {
        if (s1.size() != s2.size()) return false;
        return solve(s1, s2);
    }
};