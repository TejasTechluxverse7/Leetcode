class Solution {
public:
    int maximumLength(vector<int>& nums) {
        unordered_map<long long, int> freq;
        for (int x : nums) freq[x]++;

        int ans = 1;

        // Special case for 1 (since 1^2 = 1)
        if (freq.count(1)) {
            int c = freq[1];
            ans = max(ans, (c % 2) ? c : c - 1);
        }

        for (auto &[start, cnt] : freq) {
            if (start == 1) continue;

            long long cur = start;
            int len = 0;

            while (true) {
                int c = freq.count(cur) ? freq[cur] : 0;

                if (c >= 2) {
                    len += 2;
                    long long nxt = cur * cur;

                    if (!freq.count(nxt)) {
                        ans = max(ans, len - 1);
                        break;
                    }
                    cur = nxt;
                } 
                else if (c == 1) {
                    len++;
                    ans = max(ans, len);
                    break;
                } 
                else {
                    ans = max(ans, max(1, len - 1));
                    break;
                }
            }
        }

        return ans;
    }
};