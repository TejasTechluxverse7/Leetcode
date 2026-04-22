class Solution {
public:
    void solve(int open, int close, int n, string curr, vector<string>& result) {
        // base case
        if (curr.length() == 2 * n) {
            result.push_back(curr);
            return;
        }

        // add '(' if possible
        if (open < n) {
            solve(open + 1, close, n, curr + "(", result);
        }

        // add ')' if valid
        if (close < open) {
            solve(open, close + 1, n, curr + ")", result);
        }
    }

    vector<string> generateParenthesis(int n) {
        vector<string> result;
        solve(0, 0, n, "", result);
        return result;
    }
};