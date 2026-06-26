class Solution {
public:
    struct Fenwick {
        int n;
        vector<long long> bit;
        Fenwick(int n) : n(n), bit(n + 1, 0) {}

        void add(int idx, int val) {
            while (idx <= n) {
                bit[idx] += val;
                idx += idx & -idx;
            }
        }

        long long query(int idx) {
            long long res = 0;
            while (idx > 0) {
                res += bit[idx];
                idx -= idx & -idx;
            }
            return res;
        }
    };

    long long countMajoritySubarrays(vector<int>& nums, int target) {
        int n = nums.size();

        // Prefix sums lie in [-n, n]
        int offset = n + 1;
        Fenwick fw(2 * n + 5);

        long long ans = 0;
        int pref = 0;

        // Initial prefix sum = 0
        fw.add(offset + pref, 1);

        for (int x : nums) {
            pref += (x == target ? 1 : -1);

            // Count previous prefix sums < current prefix sum
            ans += fw.query(offset + pref - 1);

            fw.add(offset + pref, 1);
        }

        return ans;
    }
};