class Solution {
public:
    unordered_map<int, int> pos;

    TreeNode* solve(vector<int>& inorder, vector<int>& postorder,
                    int inL, int inR, int& postIndex) {
        
        if (inL > inR)
            return nullptr;

        // Last element in postorder is the root
        int rootVal = postorder[postIndex--];
        TreeNode* root = new TreeNode(rootVal);

        int mid = pos[rootVal];

        // IMPORTANT: Build right subtree first
        root->right = solve(inorder, postorder, mid + 1, inR, postIndex);
        root->left = solve(inorder, postorder, inL, mid - 1, postIndex);

        return root;
    }

    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int n = inorder.size();

        // Store position of each value in inorder
        for (int i = 0; i < n; i++)
            pos[inorder[i]] = i;

        int postIndex = n - 1;

        return solve(inorder, postorder, 0, n - 1, postIndex);
    }
};