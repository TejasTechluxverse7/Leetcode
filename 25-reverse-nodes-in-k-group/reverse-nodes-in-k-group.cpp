/**
 * Definition for singly-linked list.
 * struct ListNode {
 * int val;
 * ListNode *next;
 * ListNode() : val(0), next(nullptr) {}
 * ListNode(int x) : val(x), next(nullptr) {}
 * ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (!head || k == 1) return head;

        // Step 1: Count the total number of nodes in the list
        int count = 0;
        ListNode* curr = head;
        while (curr) {
            count++;
            curr = curr->next;
        }

        // Step 2: Setup a dummy node to easily handle head updates
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        
        ListNode* pre = dummy;
        ListNode* nex = nullptr;

        // Step 3: Loop while we have at least k nodes left to reverse
        while (count >= k) {
            curr = pre->next; // The first node of the group (will become the last)
            nex = curr->next; // The node to be moved to the front

            // Perform k-1 internal link reversals for the current group
            for (int i = 1; i < k; i++) {
                curr->next = nex->next;
                nex->next = pre->next;
                pre->next = nex;
                nex = curr->next;
            }

            // Move `pre` forward to the tail of the recently reversed group
            pre = curr;
            count -= k;
        }

        // Save the result and prevent memory leaks
        ListNode* newHead = dummy->next;
        delete dummy; 
        
        return newHead;
    }
};