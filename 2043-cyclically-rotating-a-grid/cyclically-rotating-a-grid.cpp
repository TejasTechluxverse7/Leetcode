class Solution {
public:
    vector<vector<int>> rotateGrid(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        int layers = min(m, n) / 2;

        for (int layer = 0; layer < layers; ++layer) {
            int top = layer, left = layer;
            int bottom = m - 1 - layer, right = n - 1 - layer;

            vector<int> vals;

            // top row
            for (int j = left; j <= right; ++j) vals.push_back(grid[top][j]);
            // right column
            for (int i = top + 1; i <= bottom - 1; ++i) vals.push_back(grid[i][right]);
            // bottom row
            for (int j = right; j >= left; --j) vals.push_back(grid[bottom][j]);
            // left column
            for (int i = bottom - 1; i >= top + 1; --i) vals.push_back(grid[i][left]);

            int len = vals.size();
            int shift = k % len;

            // Put back after counter-clockwise rotation:
            // same as left-rotating the clockwise traversal by shift.
            int idx = 0;

            for (int j = left; j <= right; ++j)
                grid[top][j] = vals[(shift + idx++) % len];

            for (int i = top + 1; i <= bottom - 1; ++i)
                grid[i][right] = vals[(shift + idx++) % len];

            for (int j = right; j >= left; --j)
                grid[bottom][j] = vals[(shift + idx++) % len];

            for (int i = bottom - 1; i >= top + 1; --i)
                grid[i][left] = vals[(shift + idx++) % len];
        }

        return grid;
    }
};