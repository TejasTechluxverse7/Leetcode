class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        unordered_map<int, int> mp;

        // Store reserved seats for each row using a bitmask.
        for (auto &seat : reservedSeats) {
            int row = seat[0];
            int col = seat[1];

            // Only seats 2 to 9 matter.
            if (col >= 2 && col <= 9) {
                mp[row] |= (1 << col);
            }
        }

        // Initially, every completely empty row can fit 2 groups:
        // [2,3,4,5] and [6,7,8,9]
        int ans = 2 * (n - mp.size());

        for (auto &[row, mask] : mp) {
            bool left  = !(mask & (1 << 2)) &&
                         !(mask & (1 << 3)) &&
                         !(mask & (1 << 4)) &&
                         !(mask & (1 << 5));

            bool middle = !(mask & (1 << 4)) &&
                          !(mask & (1 << 5)) &&
                          !(mask & (1 << 6)) &&
                          !(mask & (1 << 7));

            bool right = !(mask & (1 << 6)) &&
                         !(mask & (1 << 7)) &&
                         !(mask & (1 << 8)) &&
                         !(mask & (1 << 9));

            if (left && right) {
                // Two groups can sit simultaneously.
                ans += 2;
            }
            else if (left || middle || right) {
                // Only one group can be placed.
                ans += 1;
            }
        }

        return ans;
    }
};