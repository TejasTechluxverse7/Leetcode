from typing import List

class Solution:
    def combinationSum2(self, candidates: List[int], target: int) -> List[List[int]]:
        candidates.sort()
        ans = []
        path = []

        def backtrack(start: int, rem: int) -> None:
            if rem == 0:
                ans.append(path[:])
                return

            for i in range(start, len(candidates)):
                if i > start and candidates[i] == candidates[i - 1]:
                    continue
                if candidates[i] > rem:
                    break

                path.append(candidates[i])
                backtrack(i + 1, rem - candidates[i])
                path.pop()

        backtrack(0, target)
        return ans