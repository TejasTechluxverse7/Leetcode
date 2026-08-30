class Solution {
public:
    int minDepth(TreeNode* root) {
        if (root == nullptr)
            return 0;

        queue<TreeNode*> q;
        q.push(root);

        int depth = 1;

        while (!q.empty()) {
            int size = q.size();

            // Process one complete level
            for (int i = 0; i < size; i++) {
                TreeNode* node = q.front();
                q.pop();

                // First leaf found = minimum depth
                if (node->left == nullptr && node->right == nullptr)
                    return depth;

                if (node->left != nullptr)
                    q.push(node->left);

                if (node->right != nullptr)
                    q.push(node->right);
            }

            depth++;
        }

        return depth;
    }
};