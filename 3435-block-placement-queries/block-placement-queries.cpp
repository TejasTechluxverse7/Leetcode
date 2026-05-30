class Solution {
    struct SegTree {
        int n;
        vector<int> tree;

        SegTree(int n = 0) { init(n); }

        void init(int n_) {
            n = n_;
            tree.assign(4 * (n + 1), 0);
        }

        void update(int idx, int val) {
            update(1, 0, n, idx, val);
        }

        int query(int l, int r) {
            if (l > r) return 0;
            return query(1, 0, n, l, r);
        }

        void update(int node, int l, int r, int idx, int val) {
            if (l == r) {
                tree[node] = val;
                return;
            }
            int mid = (l + r) >> 1;
            if (idx <= mid) update(node << 1, l, mid, idx, val);
            else update(node << 1 | 1, mid + 1, r, idx, val);
            tree[node] = max(tree[node << 1], tree[node << 1 | 1]);
        }

        int query(int node, int l, int r, int ql, int qr) {
            if (qr < l || r < ql) return 0;
            if (ql <= l && r <= qr) return tree[node];
            int mid = (l + r) >> 1;
            return max(query(node << 1, l, mid, ql, qr),
                       query(node << 1 | 1, mid + 1, r, ql, qr));
        }
    };

public:
    vector<bool> getResults(vector<vector<int>>& queries) {
        int maxX = 0;
        for (auto &q : queries) maxX = max(maxX, q[1]);

        SegTree seg(maxX);
        set<int> obs;
        obs.insert(0);  // sentinel

        vector<bool> ans;

        for (auto &q : queries) {
            if (q[0] == 1) {
                int x = q[1];

                auto it = obs.lower_bound(x);   // first obstacle > x
                int nxt = (it == obs.end() ? -1 : *it);
                int prv = *prev(it);

                // new gap ending at x
                seg.update(x, x - prv);

                // next obstacle's gap changes because x is now its previous obstacle
                if (nxt != -1) {
                    seg.update(nxt, nxt - x);
                }

                obs.insert(x);
            } else {
                int x = q[1];
                int sz = q[2];

                auto it = obs.upper_bound(x);   // first obstacle > x
                int last = *prev(it);           // largest obstacle <= x

                int best = seg.query(0, x);      // best gap ending at some obstacle <= x
                best = max(best, x - last);     // tail gap up to x

                ans.push_back(best >= sz);
            }
        }

        return ans;
    }
};