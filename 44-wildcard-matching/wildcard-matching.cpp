class Solution {
public:
    bool isMatch(string s, string p) {
        int i = 0, j = 0;
        int star = -1;      // last position of '*' in p
        int match = 0;      // position in s after last '*'

        while (i < (int)s.size()) {
            if (j < (int)p.size() && (p[j] == s[i] || p[j] == '?')) {
                // current characters match
                i++;
                j++;
            } 
            else if (j < (int)p.size() && p[j] == '*') {
                // remember this star and where we are in s
                star = j;
                match = i;
                j++;
            } 
            else if (star != -1) {
                // mismatch, but we had a previous '*'
                j = star + 1;
                match++;
                i = match;
            } 
            else {
                return false;
            }
        }

        // remaining characters in p must all be '*'
        while (j < (int)p.size() && p[j] == '*') {
            j++;
        }

        return j == (int)p.size();
    }
};