class Solution {
public:
    bool checkValidString(string s) {
        int low = 0, high = 0;

        for (char c : s) {
            if (c == '(') {
                low++;
                high++;
            }
            else if (c == ')') {
                low--;
                high--;
            }
            else { // '*'
                low--;     // treat '*' as ')'
                high++;    // treat '*' as '('
            }

            // Minimum cannot be negative
            if (low < 0)
                low = 0;

            // Even the maximum possibility is invalid
            if (high < 0)
                return false;
        }

        return low == 0;
    }
};