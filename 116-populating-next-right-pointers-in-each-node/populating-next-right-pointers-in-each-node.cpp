class Solution {
public:
    Node* connect(Node* root) {

        if (root == NULL)
            return NULL;

        Node* level = root;

        while (level->left != NULL) {

            Node* curr = level;

            while (curr != NULL) {

                // Connect left child to right child
                curr->left->next = curr->right;

                // Connect right child to next parent's left child
                if (curr->next != NULL)
                    curr->right->next = curr->next->left;

                curr = curr->next;
            }

            // Move to the next level
            level = level->left;
        }

        return root;
    }
};