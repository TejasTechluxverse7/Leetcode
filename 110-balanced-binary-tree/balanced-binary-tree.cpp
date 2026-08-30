class Solution {
public:
    int height(TreeNode* root) {
        // Empty tree has height 0
        if (root == nullptr)
            return 0;

        int leftHeight = height(root->left);

        // Left subtree is unbalanced
        if (leftHeight == -1)
            return -1;

        int rightHeight = height(root->right);

        // Right subtree is unbalanced
        if (rightHeight == -1)
            return -1;

        // Current node is unbalanced
        if (abs(leftHeight - rightHeight) > 1)
            return -1;

        // Return height of current subtree
        return 1 + max(leftHeight, rightHeight);
    }

    bool isBalanced(TreeNode* root) {
        return height(root) != -1;
    }
};