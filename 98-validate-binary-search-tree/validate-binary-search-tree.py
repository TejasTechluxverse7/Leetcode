# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class Solution:
    def isValidBST(self, root: Optional[TreeNode]) -> bool:
        
        def validate(node, low=float('-inf'), high=float('inf')):
            # An empty tree/subtree is valid
            if not node:
                return True
            
            # The current node's value must be strictly between the low and high bounds
            if not (low < node.val < high):
                return False
            
            # Recursively validate the left and right subtrees
            # Left child inherits the current node's value as its upper bound
            # Right child inherits the current node's value as its lower bound
            return (validate(node.left, low, node.val) and 
                    validate(node.right, node.val, high))
        
        return validate(root)