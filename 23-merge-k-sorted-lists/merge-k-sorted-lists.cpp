class Solution {
public:
    
    ListNode* mergeTwo(ListNode* l1, ListNode* l2) {
        ListNode dummy(-1);
        ListNode* tail = &dummy;

        while (l1 && l2) {
            if (l1->val < l2->val) {
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }

        tail->next = l1 ? l1 : l2;
        return dummy.next;
    }

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) return NULL;

        int n = lists.size();

        while (n > 1) {
            int i = 0, j = n - 1;

            while (i < j) {
                lists[i] = mergeTwo(lists[i], lists[j]);
                i++;
                j--;
            }

            n = (n + 1) / 2;
        }

        return lists[0];
    }
};