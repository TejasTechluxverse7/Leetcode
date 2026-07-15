# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class Solution:
    def generateTrees(self, n: int) -> List[Optional[TreeNode]]:
        from functools import lru_cache

        @lru_cache(None)
        def build(start, end):
            if start > end:
                return [None]

            trees = []

            for rootVal in range(start, end + 1):
                leftTrees = build(start, rootVal - 1)
                rightTrees = build(rootVal + 1, end)

                for left in leftTrees:
                    for right in rightTrees:
                        root = TreeNode(rootVal)
                        root.left = left
                        root.right = right
                        trees.append(root)

            return trees

        return build(1, n)