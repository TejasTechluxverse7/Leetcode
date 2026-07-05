class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        const int MOD = 1e9 + 7;
        int n = board.size();

        vector<vector<int>> dpScore(n, vector<int>(n, -1));
        vector<vector<int>> dpCount(n, vector<int>(n, 0));

        dpScore[0][0] = 0;
        dpCount[0][0] = 1;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 'X') continue;
                if (i == 0 && j == 0) continue;

                int best = -1;
                long long ways = 0;

                vector<pair<int,int>> prev = {
                    {i - 1, j},
                    {i, j - 1},
                    {i - 1, j - 1}
                };

                for (auto &[x, y] : prev) {
                    if (x < 0 || y < 0) continue;
                    if (dpScore[x][y] == -1) continue;

                    if (dpScore[x][y] > best) {
                        best = dpScore[x][y];
                        ways = dpCount[x][y];
                    } else if (dpScore[x][y] == best) {
                        ways = (ways + dpCount[x][y]) % MOD;
                    }
                }

                if (best == -1) continue;

                int val = 0;
                if (board[i][j] >= '1' && board[i][j] <= '9')
                    val = board[i][j] - '0';

                dpScore[i][j] = best + val;
                dpCount[i][j] = ways % MOD;
            }
        }

        if (dpScore[n - 1][n - 1] == -1)
            return {0, 0};

        return {dpScore[n - 1][n - 1], dpCount[n - 1][n - 1]};
    }
};