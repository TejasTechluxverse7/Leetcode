class Solution {
public:
    int minJumps(vector<int>& nums) {
        int n = (int)nums.size();
        if (n == 1) return 0;

        int mx = *max_element(nums.begin(), nums.end());

        // Smallest Prime Factor sieve
        vector<int> spf(mx + 1, 0);
        spf[1] = 1;
        for (int i = 2; i <= mx; ++i) {
            if (spf[i] == 0) { // i is prime
                spf[i] = i;
                if (1LL * i * i <= mx) {
                    for (long long j = 1LL * i * i; j <= mx; j += i) {
                        if (spf[(int)j] == 0) spf[(int)j] = i;
                    }
                }
            }
        }

        // For each prime p, store all indices whose value is divisible by p
        unordered_map<int, vector<int>> bucket;
        bucket.reserve(n * 2);

        for (int i = 0; i < n; ++i) {
            int x = nums[i];
            while (x > 1) {
                int p = spf[x];
                bucket[p].push_back(i);
                while (x % p == 0) x /= p; // keep only distinct prime factors
            }
        }

        vector<char> visited(n, 0);
        vector<char> usedPrime(mx + 1, 0);

        queue<int> q;
        q.push(0);
        visited[0] = 1;

        int jumps = 0;

        while (!q.empty()) {
            int sz = (int)q.size();
            while (sz--) {
                int i = q.front();
                q.pop();

                if (i == n - 1) return jumps;

                // Adjacent steps
                if (i - 1 >= 0 && !visited[i - 1]) {
                    visited[i - 1] = 1;
                    q.push(i - 1);
                }
                if (i + 1 < n && !visited[i + 1]) {
                    visited[i + 1] = 1;
                    q.push(i + 1);
                }

                // Prime teleportation
                int p = nums[i];
                if (p > 1 && spf[p] == p && !usedPrime[p]) {
                    usedPrime[p] = 1;

                    auto it = bucket.find(p);
                    if (it != bucket.end()) {
                        for (int j : it->second) {
                            if (!visited[j]) {
                                visited[j] = 1;
                                q.push(j);
                            }
                        }
                        it->second.clear(); // avoid scanning again
                    }
                }
            }
            ++jumps;
        }

        return -1;
    }
};