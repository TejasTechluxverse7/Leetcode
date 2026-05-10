class Solution {
public:
    void backtrack(int start, int target, vector<int>& candidates,
                   vector<int>& path, vector<vector<int>>& ans) {
        if (target == 0) {
            ans.push_back(path);
            return;
        }

        for (int i = start; i < candidates.size(); i++) {
            // Skip duplicates at the same level
            if (i > start && candidates[i] == candidates[i - 1]) continue;

            // Since array is sorted, no need to continue further
            if (candidates[i] > target) break;

            path.push_back(candidates[i]);
            backtrack(i + 1, target - candidates[i], candidates, path, ans);
            path.pop_back();
        }
    }

    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> ans;
        vector<int> path;
        backtrack(0, target, candidates, path, ans);
        return ans;
    }
};