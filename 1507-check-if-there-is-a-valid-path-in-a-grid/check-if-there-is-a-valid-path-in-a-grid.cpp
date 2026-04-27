class Solution {
public:
    bool hasValidPath(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // directions: up, right, down, left
        vector<int> dx = {-1, 0, 1, 0};
        vector<int> dy = {0, 1, 0, -1};

        // opposite direction mapping
        vector<int> opp = {2, 3, 0, 1};

        // allowed directions for each street type
        vector<vector<int>> dirs = {
            {},             // dummy (0 unused)
            {3, 1},         // type 1 -> left, right
            {0, 2},         // type 2 -> up, down
            {3, 2},         // type 3 -> left, down
            {1, 2},         // type 4 -> right, down
            {3, 0},         // type 5 -> left, up
            {1, 0}          // type 6 -> right, up
        };

        queue<pair<int,int>> q;
        vector<vector<bool>> vis(m, vector<bool>(n, false));

        q.push({0,0});
        vis[0][0] = true;

        while(!q.empty()) {
            auto [x, y] = q.front();
            q.pop();

            if(x == m-1 && y == n-1)
                return true;

            int type = grid[x][y];

            for(int d : dirs[type]) {
                int nx = x + dx[d];
                int ny = y + dy[d];

                if(nx < 0 || ny < 0 || nx >= m || ny >= n)
                    continue;

                if(vis[nx][ny])
                    continue;

                int nextType = grid[nx][ny];

                // check if neighbor connects back
                bool valid = false;
                for(int nd : dirs[nextType]) {
                    if(nd == opp[d]) {
                        valid = true;
                        break;
                    }
                }

                if(valid) {
                    vis[nx][ny] = true;
                    q.push({nx, ny});
                }
            }
        }

        return false;
    }
};