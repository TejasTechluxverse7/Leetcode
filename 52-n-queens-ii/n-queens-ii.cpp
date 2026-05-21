class Solution {
public:
    int totalNQueens(int n) {
        int count = 0;
        vector<int> col(n, 0), diag1(2 * n - 1, 0), diag2(2 * n - 1, 0);

        function<void(int)> backtrack = [&](int row) {
            if (row == n) {
                count++;
                return;
            }

            for (int c = 0; c < n; c++) {
                int d1 = row + c;           // main diagonal
                int d2 = row - c + n - 1;   // anti-diagonal

                if (col[c] || diag1[d1] || diag2[d2]) continue;

                col[c] = diag1[d1] = diag2[d2] = 1;
                backtrack(row + 1);
                col[c] = diag1[d1] = diag2[d2] = 0;
            }
        };

        backtrack(0);
        return count;
    }
};