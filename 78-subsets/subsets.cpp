class Solution {
public:
    vector<vector<int>> ans;

    void dfs(int idx, vector<int>& nums, vector<int>& curr) {
        if (idx == nums.size()) {
            ans.push_back(curr);
            return;
        }

        // Exclude nums[idx]
        dfs(idx + 1, nums, curr);

        // Include nums[idx]
        curr.push_back(nums[idx]);
        dfs(idx + 1, nums, curr);
        curr.pop_back();
    }

    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> curr;
        dfs(0, nums, curr);
        return ans;
    }
};