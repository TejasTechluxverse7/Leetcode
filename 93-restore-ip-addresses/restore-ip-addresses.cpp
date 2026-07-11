class Solution {
public:
    vector<string> ans;

    void backtrack(string &s, int idx, int parts, string curr) {
        // If 4 parts are formed
        if (parts == 4) {
            if (idx == s.size()) {
                curr.pop_back();          // Remove last '.'
                ans.push_back(curr);
            }
            return;
        }

        // Try segments of length 1 to 3
        for (int len = 1; len <= 3 && idx + len <= s.size(); len++) {
            string part = s.substr(idx, len);

            // Leading zero is not allowed
            if (part.size() > 1 && part[0] == '0')
                break;

            int val = stoi(part);

            if (val <= 255) {
                backtrack(s, idx + len, parts + 1, curr + part + ".");
            }
        }
    }

    vector<string> restoreIpAddresses(string s) {
        if (s.size() < 4 || s.size() > 12)
            return {};

        backtrack(s, 0, 0, "");
        return ans;
    }
};