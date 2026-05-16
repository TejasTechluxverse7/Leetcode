from typing import List

class Solution:
    def permute(self, nums: List[int]) -> List[List[int]]:
        result = []

        def backtrack(path, remaining):
            # If no elements left, store permutation
            if not remaining:
                result.append(path)
                return

            # Try each number
            for i in range(len(remaining)):
                backtrack(
                    path + [remaining[i]],                 # add current number
                    remaining[:i] + remaining[i+1:]       # remaining numbers
                )

        backtrack([], nums)
        return result