class Solution {
public:
    vector<vector<string>> ans;

    void backtrack(int row, int n, vector<string>& board,
                   vector<int>& colUsed, vector<int>& diag1, vector<int>& diag2) {
        if (row == n) {
            ans.push_back(board);
            return;
        }

        for (int col = 0; col < n; col++) {
            int d1 = row - col + n - 1;  // main diagonal
            int d2 = row + col;          // anti-diagonal

            if (colUsed[col] || diag1[d1] || diag2[d2]) continue;

            board[row][col] = 'Q';
            colUsed[col] = diag1[d1] = diag2[d2] = 1;

            backtrack(row + 1, n, board, colUsed, diag1, diag2);

            board[row][col] = '.';
            colUsed[col] = diag1[d1] = diag2[d2] = 0;
        }
    }

    vector<vector<string>> solveNQueens(int n) {
        vector<string> board(n, string(n, '.'));
        vector<int> colUsed(n, 0);
        vector<int> diag1(2 * n - 1, 0);
        vector<int> diag2(2 * n - 1, 0);

        backtrack(0, n, board, colUsed, diag1, diag2);
        return ans;
    }
};