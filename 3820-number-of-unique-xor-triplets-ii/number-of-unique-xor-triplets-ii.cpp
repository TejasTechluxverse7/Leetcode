class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        const int MAXX = 2048; // nums[i] <= 1500 < 2^11

        vector<bitset<MAXX>> dp(4), ndp(4);
        dp[0][0] = 1;

        for (int v : nums) {
            ndp = dp; // choosing this index 0 times

            for (int taken = 0; taken <= 3; taken++) {
                for (int x = 0; x < MAXX; x++) {
                    if (!dp[taken][x]) continue;

                    for (int add = 1; taken + add <= 3; add++) {
                        int contrib = (add & 1) ? v : 0;
                        ndp[taken + add][x ^ contrib] = 1;
                    }
                }
            }

            dp.swap(ndp);
        }

        return dp[3].count();
    }
};