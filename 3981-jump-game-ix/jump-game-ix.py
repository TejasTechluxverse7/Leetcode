from typing import List

class Solution:
    def maxValue(self, nums: List[int]) -> List[int]:
        n = len(nums)

        # suffix minimum array
        sufMin = [float('inf')] * (n + 1)

        for i in range(n - 1, -1, -1):
            sufMin[i] = min(sufMin[i + 1], nums[i])

        ans = [0] * n

        l = 0
        mx = nums[0]

        for r in range(n):
            mx = max(mx, nums[r])

            # end of connected component
            if r == n - 1 or mx <= sufMin[r + 1]:
                for i in range(l, r + 1):
                    ans[i] = mx

                l = r + 1

                if l < n:
                    mx = nums[l]

        return ans