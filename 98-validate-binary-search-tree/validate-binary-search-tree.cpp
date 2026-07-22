/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        return validate(root, nullptr, nullptr);
    }
    
private:
    bool validate(TreeNode* node, TreeNode* low, TreeNode* high) {
        // An empty tree/subtree is valid
        if (node == nullptr) {
            return true;
        }
        
        // The current node's value must be strictly between the low and high bounds
        if ((low != nullptr && node->val <= low->val) || 
            (high != nullptr && node->val >= high->val)) {
            return false;
        }
        
        // Recursively validate the left and right subtrees
        // For the left subtree, the current node becomes the upper bound (high)
        // For the right subtree, the current node becomes the lower bound (low)
        return validate(node->left, low, node) && 
               validate(node->right, node, high);
    }
};