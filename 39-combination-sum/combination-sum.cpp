class Solution {
public:
    void backtrack(int start, int target, vector<int>& candidates,
                   vector<int>& path, vector<vector<int>>& ans) {
        if (target == 0) {
            ans.push_back(path);
            return;
        }

        for (int i = start; i < (int)candidates.size(); i++) {
            if (candidates[i] > target) break;

            path.push_back(candidates[i]);
            backtrack(i, target - candidates[i], candidates, path, ans); // i, not i+1
            path.pop_back();
        }
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> ans;
        vector<int> path;
        backtrack(0, target, candidates, path, ans);
        return ans;
    }
};