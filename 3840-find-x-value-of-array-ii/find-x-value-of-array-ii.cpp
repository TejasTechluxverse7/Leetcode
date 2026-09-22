class Solution {
public:
    struct Node {
        int prod;
        int pref[5];

        Node() {
            prod = 1;
            for (int i = 0; i < 5; i++)
                pref[i] = 0;
        }
    };

    int n, k;
    vector<Node> seg;

    inline Node mergeNode(const Node& L, const Node& R) {
        Node res;

        res.prod = (1LL * L.prod * R.prod) % k;

        // Prefixes completely inside L
        for (int r = 0; r < k; r++) {
            res.pref[r] = L.pref[r];
        }

        // Prefixes which extend into R
        for (int r = 0; r < k; r++) {
            if (R.pref[r]) {
                int nr = (1LL * L.prod * r) % k;
                res.pref[nr] += R.pref[r];
            }
        }

        return res;
    }

    void build(int p, int l, int r, const vector<int>& nums) {
        if (l == r) {
            int rem = nums[l] % k;

            seg[p].prod = rem;
            seg[p].pref[rem] = 1;

            return;
        }

        int mid = (l + r) >> 1;

        build(p << 1, l, mid, nums);
        build(p << 1 | 1, mid + 1, r, nums);

        seg[p] = mergeNode(seg[p << 1], seg[p << 1 | 1]);
    }

    void update(int p, int l, int r, int idx, int val) {
        if (l == r) {
            // Reset node
            seg[p].prod = val % k;

            for (int i = 0; i < k; i++)
                seg[p].pref[i] = 0;

            seg[p].pref[seg[p].prod] = 1;

            return;
        }

        int mid = (l + r) >> 1;

        if (idx <= mid)
            update(p << 1, l, mid, idx, val);
        else
            update(p << 1 | 1, mid + 1, r, idx, val);

        seg[p] = mergeNode(seg[p << 1], seg[p << 1 | 1]);
    }

    Node query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr)
            return seg[p];

        int mid = (l + r) >> 1;

        if (qr <= mid)
            return query(p << 1, l, mid, ql, qr);

        if (ql > mid)
            return query(p << 1 | 1, mid + 1, r, ql, qr);

        Node L = query(p << 1, l, mid, ql, qr);
        Node R = query(p << 1 | 1, mid + 1, r, ql, qr);

        return mergeNode(L, R);
    }

    vector<int> resultArray(
        vector<int>& nums,
        int K,
        vector<vector<int>>& queries
    ) {
        n = nums.size();
        k = K;

        seg.resize(4 * n + 5);

        build(1, 0, n - 1, nums);

        vector<int> ans;
        ans.reserve(queries.size());

        for (const auto& q : queries) {
            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

            // Persistent update
            nums[index] = value;
            update(1, 0, n - 1, index, value);

            // Prefix products of nums[start ... n-1]
            Node res = query(1, 0, n - 1, start, n - 1);

            ans.push_back(res.pref[x]);
        }

        return ans;
    }
};