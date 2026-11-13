#include <vector>
#include <deque>

using namespace std;

class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        long long ans = 0;
        long long cost = 0;
        
        // Monotonic deque storing pairs of {target_value, count_of_elements}
        // Values are strictly decreasing from front to back
        deque<pair<long long, int>> dq;
        
        int r = n - 1;
        for (int l = n - 1; l >= 0; --l) {
            long long val = nums[l];
            int count = 1;
            
            // Merge smaller segments to the right up to the current element's value
            while (!dq.empty() && dq.front().first < val) {
                auto [prev_val, prev_count] = dq.front();
                dq.pop_front();
                
                cost += (val - prev_val) * prev_count;
                count += prev_count;
            }
            dq.push_front({val, count});
            
            // Shrink the window from the right until total operations <= k
            while (cost > k) {
                auto& [back_val, back_count] = dq.back();
                cost -= (back_val - nums[r]);
                
                if (--back_count == 0) {
                    dq.pop_back();
                }
                --r;
            }
            
            // All subarrays starting at l and ending in [l, r] are valid
            ans += (r - l + 1);
        }
        
        return ans;
    }
};