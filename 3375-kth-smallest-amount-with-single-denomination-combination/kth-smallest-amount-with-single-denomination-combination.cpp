class Solution {
public:
    long long findKthSmallest(vector<int>& coins, int k) {
        int n = coins.size();

        // lcm of two numbers, capped to avoid overflow
        auto lcm = [](long long a, long long b) -> long long {
            long long g = std::gcd(a, b);
            long long x = a / g;
            if (x > (long long)4e18 / b) return (long long)4e18;
            return x * b;
        };

        // Count numbers <= x divisible by at least one coin.
        auto count = [&](long long x) -> long long {
            long long ans = 0;

            // Inclusion-exclusion over all subsets
            for (int mask = 1; mask < (1 << n); mask++) {
                long long L = 1;
                int bits = 0;
                bool ok = true;

                for (int i = 0; i < n; i++) {
                    if (mask & (1 << i)) {
                        bits++;
                        L = lcm(L, coins[i]);

                        if (L > x) {
                            ok = false;
                            break;
                        }
                    }
                }

                if (!ok) continue;

                long long cnt = x / L;

                if (bits & 1)
                    ans += cnt;
                else
                    ans -= cnt;
            }

            return ans;
        };

        // The kth answer is at most min(coins) * k
        long long lo = 1;
        long long hi = 1LL * (*min_element(coins.begin(), coins.end())) * k;

        while (lo < hi) {
            long long mid = lo + (hi - lo) / 2;

            if (count(mid) >= k)
                hi = mid;
            else
                lo = mid + 1;
        }

        return lo;
    }
};