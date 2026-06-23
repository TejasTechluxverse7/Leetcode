class Solution {
public:
    static const int MOD = 1000000007;

    int zigZagArrays(int n, int l, int r) {
        int m = r - l + 1;

        // Allocate reusable buffers once to avoid overhead inside the loop
        vector<long long> up(m + 2, 0);
        vector<long long> down(m + 2, 0);
        vector<long long> next_up(m + 2, 0);
        vector<long long> next_down(m + 2, 0);
        vector<long long> prefDown(m + 2, 0);
        vector<long long> suffUp(m + 2, 0);

        // Base case: Length = 2
        for (int v = 1; v <= m; v++) {
            up[v] = v - 1;
            down[v] = m - v;
        }

        // Build lengths 3 to n
        for (int len = 3; len <= n; len++) {
            // Build Prefix Sum for Down
            for (int i = 1; i <= m; i++) {
                prefDown[i] = prefDown[i - 1] + down[i];
                if (prefDown[i] >= MOD) prefDown[i] %= MOD;
            }

            // Build Suffix Sum for Up
            suffUp[m + 1] = 0;
            for (int i = m; i >= 1; i--) {
                suffUp[i] = suffUp[i + 1] + up[i];
                if (suffUp[i] >= MOD) suffUp[i] %= MOD;
            }

            // Transition directly into our secondary buffer
            for (int v = 1; v <= m; v++) {
                next_up[v] = prefDown[v - 1];
                next_down[v] = suffUp[v + 1];
            }

            // Swap the data pointers (O(1) operation) instead of reallocating
            up.swap(next_up);
            down.swap(next_down);
        }

        // Aggregate total configurations
        long long ans = 0;
        for (int v = 1; v <= m; v++) {
            ans += up[v] + down[v];
            if (ans >= MOD) ans %= MOD;
        }

        return (int)ans;
    }
};