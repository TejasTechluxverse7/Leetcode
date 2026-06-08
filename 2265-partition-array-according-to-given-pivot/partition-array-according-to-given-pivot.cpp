class Solution {
public:
    vector<int> pivotArray(vector<int>& nums, int pivot) {
        vector<int> less, equal, greater;

        for (int num : nums) {
            if (num < pivot)
                less.push_back(num);
            else if (num == pivot)
                equal.push_back(num);
            else
                greater.push_back(num);
        }

        vector<int> ans;

        for (int x : less) ans.push_back(x);
        for (int x : equal) ans.push_back(x);
        for (int x : greater) ans.push_back(x);

        return ans;
    }
};