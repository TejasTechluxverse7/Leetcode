class Solution {
public:
    vector<long long> distance(vector<int>& nums) {
        int n = nums.size();
        vector<long long> result(n, 0);

        unordered_map<int, vector<int>> mp;

        // Step 1: store indices for each value
        for (int i = 0; i < n; i++) {
            mp[nums[i]].push_back(i);
        }

        // Step 2: process each group
        for (auto &it : mp) {
            vector<int> &pos = it.second;
            int k = pos.size();

            vector<long long> prefix(k + 1, 0);

            // prefix sum
            for (int i = 0; i < k; i++) {
                prefix[i + 1] = prefix[i] + pos[i];
            }

            // compute result for each index
            for (int i = 0; i < k; i++) {
                long long left = (long long)pos[i] * i - prefix[i];
                long long right = (prefix[k] - prefix[i + 1]) - (long long)pos[i] * (k - i - 1);
                result[pos[i]] = left + right;
            }
        }

        return result;
    }
};