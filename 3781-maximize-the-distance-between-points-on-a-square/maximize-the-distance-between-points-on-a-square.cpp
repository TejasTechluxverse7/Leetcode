#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxDistance(int side, vector<vector<int>>& points, int k) {
        int n = points.size();
        vector<long long> A(n);
        
        // Step 1: Map 2D perimeter points to 1D distances [0, 4 * side)
        for (int i = 0; i < n; ++i) {
            long long x = points[i][0];
            long long y = points[i][1];
            
            if (y == 0) {
                A[i] = x;                               // Bottom edge
            } else if (x == side) {
                A[i] = side + y;                        // Right edge
            } else if (y == side) {
                A[i] = 2LL * side + (side - x);         // Top edge
            } else {
                A[i] = 3LL * side + (side - y);         // Left edge
            }
        }
        
        sort(A.begin(), A.end());
        
        // Step 2: Duplicate the array to handle the cyclic "wrap-around" natively
        long long P = 4LL * side;
        vector<long long> A2(2 * n);
        for (int i = 0; i < n; ++i) {
            A2[i] = A[i];
            A2[i + n] = A[i] + P;
        }
        
        // Step 3: Validation function for our Binary Search
        auto check = [&](long long D) {
            // Precompute the next valid index for every element if we require distance D
            vector<int> nxt(2 * n);
            int r = 0;
            for (int l = 0; l < 2 * n; ++l) {
                while (r < 2 * n && A2[r] - A2[l] < D) {
                    r++;
                }
                nxt[l] = r;
            }
            
            // Try starting our k-selection from each original point
            for (int i = 0; i < n; ++i) {
                int curr = i;
                bool possible = true;
                
                // Make k - 1 jumps to select k points
                for (int step = 1; step < k; ++step) {
                    curr = nxt[curr];
                    if (curr >= 2 * n) {
                        possible = false;
                        break;
                    }
                }
                
                // Check if the final jump wraps around past our original starting point
                if (possible && (A2[i] + P - A2[curr] >= D)) {
                    return true;
                }
            }
            return false;
        };
        
        // Step 4: Binary Search over the possible distance space
        long long low = 1, high = side;
        int ans = 0;
        
        while (low <= high) {
            long long mid = low + (high - low) / 2;
            if (check(mid)) {
                ans = mid;        // mid is possible, try for a larger distance
                low = mid + 1;
            } else {
                high = mid - 1;   // mid is impossible, shrink search space
            }
        }
        
        return ans;
    }
};