class Solution {
public:
    int minMoves(vector<int>& nums, int limit) {
        int n = nums.size();
        int maxSum = 2 * limit;

        // diff array for range updates on cost by sum
        vector<int> diff(maxSum + 2, 0);

        for (int i = 0; i < n / 2; i++) {
            int a = nums[i];
            int b = nums[n - 1 - i];

            int low = min(a, b) + 1;
            int high = max(a, b) + limit;
            int sum = a + b;

            // By default, 2 moves are needed for every target sum
            diff[2] += 2;
            diff[maxSum + 1] -= 2;

            // 1 move is enough for target sums in [low, high]
            diff[low] -= 1;
            diff[high + 1] += 1;

            // 0 moves needed for the exact current sum
            diff[sum] -= 1;
            diff[sum + 1] += 1;
        }

        int ans = n;
        int curr = 0;
        for (int s = 2; s <= maxSum; s++) {
            curr += diff[s];
            ans = min(ans, curr);
        }

        return ans;
    }
};