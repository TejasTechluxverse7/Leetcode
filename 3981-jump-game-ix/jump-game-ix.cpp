class Solution {
public:
    vector<int> maxValue(vector<int>& nums) {
        int n = (int)nums.size();
        vector<int> sufMin(n + 1, INT_MAX);

        // sufMin[i] = minimum value in nums[i...n-1]
        for (int i = n - 1; i >= 0; --i) {
            sufMin[i] = min(sufMin[i + 1], nums[i]);
        }

        vector<int> ans(n);
        int l = 0;          // start of current component
        int mx = nums[0];   // max inside current component

        for (int r = 0; r < n; ++r) {
            mx = max(mx, nums[r]);

            // If no inversion crosses the cut after r, close this component
            if (r == n - 1 || mx <= sufMin[r + 1]) {
                for (int i = l; i <= r; ++i) {
                    ans[i] = mx;
                }
                l = r + 1;
                if (l < n) mx = nums[l];
            }
        }

        return ans;
    }
};