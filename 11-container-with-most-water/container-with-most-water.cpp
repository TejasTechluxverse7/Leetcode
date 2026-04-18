#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0;
        int right = height.size() - 1;
        int max_water = 0;
        
        while (left < right) {
            // Calculate the area with the current left and right pointers
            int current_width = right - left;
            int current_height = min(height[left], height[right]);
            int current_area = current_width * current_height;
            
            // Update the maximum water found so far
            max_water = max(max_water, current_area);
            
            // Move the pointer pointing to the shorter line inward
            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }
        
        return max_water;
    }
};