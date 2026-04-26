class Solution {
public:
    int m, n;
    vector<vector<int>> vis;
    
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
    
    bool dfs(vector<vector<char>>& grid, int x, int y, int px, int py) {
        vis[x][y] = 1;
        
        for(int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            
            // boundary check
            if(nx < 0 || ny < 0 || nx >= m || ny >= n)
                continue;
            
            // must have same character
            if(grid[nx][ny] != grid[x][y])
                continue;
            
            // don't go back to parent
            if(nx == px && ny == py)
                continue;
            
            // already visited -> cycle found
            if(vis[nx][ny])
                return true;
            
            if(dfs(grid, nx, ny, x, y))
                return true;
        }
        
        return false;
    }
    
    bool containsCycle(vector<vector<char>>& grid) {
        m = grid.size();
        n = grid[0].size();
        
        vis.assign(m, vector<int>(n, 0));
        
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(!vis[i][j]) {
                    if(dfs(grid, i, j, -1, -1))
                        return true;
                }
            }
        }
        
        return false;
    }
};