class Solution {
public:
    Node* connect(Node* root) {

        if (root == NULL)
            return NULL;

        Node* curr = root;

        while (curr != NULL) {

            // Dummy node for the next level
            Node dummy(0);
            Node* tail = &dummy;

            // Traverse current level using next pointers
            while (curr != NULL) {

                if (curr->left != NULL) {
                    tail->next = curr->left;
                    tail = tail->next;
                }

                if (curr->right != NULL) {
                    tail->next = curr->right;
                    tail = tail->next;
                }

                curr = curr->next;
            }

            // Move to the first node of next level
            curr = dummy.next;
        }

        return root;
    }
};