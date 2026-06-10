#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

class Solution {
    struct Node {
        int val;
        int start_idx;
        long long pref_sum;
    };

    // Helper method to count how many subarrays have (max - min) >= T
    long long countGE(long long T, const vector<int>& nums) {
        long long count = 0;
        int left = 0;
        deque<int> max_dq, min_dq;
        for (int r = 0; r < nums.size(); ++r) {
            // Maintain rolling max window
            while (!max_dq.empty() && nums[max_dq.back()] <= nums[r]) max_dq.pop_back();
            max_dq.push_back(r);
            // Maintain rolling min window
            while (!min_dq.empty() && nums[min_dq.back()] >= nums[r]) min_dq.pop_back();
            min_dq.push_back(r);
            
            // Shrink window while difference is valid for our threshold 
            while (!max_dq.empty() && !min_dq.empty() && nums[max_dq.front()] - nums[min_dq.front()] >= T) {
                left++;
                if (max_dq.front() < left) max_dq.pop_front();
                if (min_dq.front() < left) min_dq.pop_front();
            }
            // All start indices from 0 to left-1 (which is `left` count in total) 
            // paired with right boundary `r` are guaranteed to have a difference >= T
            count += left;
        }
        return count;
    }

    // Binary searches within the monotonic stack to find the running prefix sum up to end_l
    long long query(const vector<Node>& stk, int end_l) {
        if (end_l < 0) return 0;
        int low = 0, high = stk.size() - 1;
        int idx = 0;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (stk[mid].start_idx <= end_l) {
                idx = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        long long sum = 0;
        if (idx > 0) sum += stk[idx - 1].pref_sum;
        sum += (long long)stk[idx].val * (end_l - stk[idx].start_idx + 1);
        return sum;
    }

public:
    long long maxTotalValue(vector<int>& nums, int k) {
        // Step 1: Binary search the k-th largest value
        long long low = 0, high = 1e9, X = 0;
        while(low <= high) {
            long long mid = low + (high - low) / 2;
            if (countGE(mid, nums) >= k) {
                X = mid;
                low = mid + 1; // Try to find a stricter (higher) boundary
            } else {
                high = mid - 1;
            }
        }

        // Step 2: Extract sum of elements >= (X + 1)
        long long T = X + 1;
        long long C_T = 0;
        long long S_T = 0;
        int left = 0;
        
        deque<int> max_dq, min_dq;
        vector<Node> stk_max, stk_min;

        for (int r = 0; r < nums.size(); ++r) {
            // Update deque for sliding window
            while (!max_dq.empty() && nums[max_dq.back()] <= nums[r]) max_dq.pop_back();
            max_dq.push_back(r);
            while (!min_dq.empty() && nums[min_dq.back()] >= nums[r]) min_dq.pop_back();
            min_dq.push_back(r);
            
            while (!max_dq.empty() && !min_dq.empty() && nums[max_dq.front()] - nums[min_dq.front()] >= T) {
                left++;
                if (max_dq.front() < left) max_dq.pop_front();
                if (min_dq.front() < left) min_dq.pop_front();
            }
            
            C_T += left;

            // Maintain max monotonic prefix sum stack
            int new_start_max = r;
            while (!stk_max.empty() && stk_max.back().val <= nums[r]) {
                new_start_max = stk_max.back().start_idx;
                stk_max.pop_back();
            }
            long long pref_max = stk_max.empty() ? 0 : stk_max.back().pref_sum;
            long long contrib_max = (long long)nums[r] * (r - new_start_max + 1);
            stk_max.push_back({nums[r], new_start_max, pref_max + contrib_max});

            // Maintain min monotonic prefix sum stack
            int new_start_min = r;
            while (!stk_min.empty() && stk_min.back().val >= nums[r]) {
                new_start_min = stk_min.back().start_idx;
                stk_min.pop_back();
            }
            long long pref_min = stk_min.empty() ? 0 : stk_min.back().pref_sum;
            long long contrib_min = (long long)nums[r] * (r - new_start_min + 1);
            stk_min.push_back({nums[r], new_start_min, pref_min + contrib_min});

            // If we have valid subarrays passing the strict threshold, add their differences safely 
            if (left > 0) {
                S_T += query(stk_max, left - 1) - query(stk_min, left - 1);
            }
        }

        // Final result equals sum of elements strictly > X, plus padding the remainder exactly equal to X 
        return S_T + (long long)(k - C_T) * X;
    }
};