class Solution:
    def combinationSum(self, candidates: List[int], target: int) -> List[List[int]]:
        candidates.sort()
        ans = []
        path = []

        def backtrack(start: int, remaining: int) -> None:
            if remaining == 0:
                ans.append(path[:])
                return

            for i in range(start, len(candidates)):
                if candidates[i] > remaining:
                    break

                path.append(candidates[i])
                backtrack(i, remaining - candidates[i])  # reuse allowed
                path.pop()

        backtrack(0, target)
        return ans