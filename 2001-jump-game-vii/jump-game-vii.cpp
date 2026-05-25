class Solution {
public:
    bool canReach(string s, int minJump, int maxJump) {
        int n = s.size();
        vector<bool> vis(n, false);
        queue<int> q;

        q.push(0);
        vis[0] = true;

        int far = 0;  // farthest index we have already processed for adding new nodes

        while (!q.empty()) {
            int i = q.front();
            q.pop();

            int start = max(i + minJump, far + 1);
            int end = min(i + maxJump, n - 1);

            for (int j = start; j <= end; ++j) {
                if (s[j] == '0' && !vis[j]) {
                    vis[j] = true;
                    if (j == n - 1) return true;
                    q.push(j);
                }
            }

            far = max(far, end);
        }

        return vis[n - 1];
    }
};