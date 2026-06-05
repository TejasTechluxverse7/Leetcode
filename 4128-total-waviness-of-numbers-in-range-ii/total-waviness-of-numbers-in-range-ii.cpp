class Solution {
public:
    struct State {
        long long cnt = 0;
        long long sum = 0;
        bool vis = false;
    };

    vector<int> dig;
    State dp[17][2][17][11][11];

    pair<long long, long long> dfs(int pos, bool tight,
                                   bool started, int len,
                                   int last1, int last2) {
        if (pos == (int)dig.size()) {
            return {1, 0};
        }

        if (!tight && dp[pos][started][len][last1 + 1][last2 + 1].vis) {
            auto &cur = dp[pos][started][len][last1 + 1][last2 + 1];
            return {cur.cnt, cur.sum};
        }

        long long totalCnt = 0;
        long long totalSum = 0;

        int limit = tight ? dig[pos] : 9;

        for (int d = 0; d <= limit; d++) {
            bool ntight = tight && (d == limit);

            if (!started && d == 0) {
                auto nxt = dfs(pos + 1, ntight, false, 0, -1, -1);
                totalCnt += nxt.first;
                totalSum += nxt.second;
            } else {
                if (!started) {
                    auto nxt = dfs(pos + 1, ntight, true, 1, d, -1);
                    totalCnt += nxt.first;
                    totalSum += nxt.second;
                } else if (len == 1) {
                    auto nxt = dfs(pos + 1, ntight, true, 2, d, last1);
                    totalCnt += nxt.first;
                    totalSum += nxt.second;
                } else {
                    int contrib = 0;

                    if ((last1 > last2 && last1 > d) ||
                        (last1 < last2 && last1 < d)) {
                        contrib = 1;
                    }

                    auto nxt = dfs(pos + 1, ntight, true, len + 1, d, last1);

                    totalCnt += nxt.first;
                    totalSum += nxt.second + nxt.first * contrib;
                }
            }
        }

        if (!tight) {
            auto &cur = dp[pos][started][len][last1 + 1][last2 + 1];
            cur.vis = true;
            cur.cnt = totalCnt;
            cur.sum = totalSum;
        }

        return {totalCnt, totalSum};
    }

    long long solve(long long N) {
        if (N < 0) return 0;

        dig.clear();
        for (char c : to_string(N)) dig.push_back(c - '0');

        memset(dp, 0, sizeof(dp));

        return dfs(0, true, false, 0, -1, -1).second;
    }

    long long totalWaviness(long long num1, long long num2) {
        return solve(num2) - solve(num1 - 1);
    }
};