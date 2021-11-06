/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

struct Solution final {
    ListNode* oddEvenList(ListNode *head) const {
        ListNode *head_even = nullptr;
        ListNode *tail_even = nullptr;
        ListNode *head_odd = nullptr;
        ListNode *tail_odd = nullptr;
        ListNode *n = head;
        
        for (int i = 1; n != nullptr; ++i) {
            auto next = n->next;
            n->next = nullptr;
            
            if (i % 2) {
                if (!head_odd) {
                    head_odd = n;
                    tail_odd = n;
                } else {
                    tail_odd->next = n;
                    tail_odd = n;
                }
            } else {
                if (!head_even) {
                    head_even = n;
                    tail_even = n;
                } else {
                    tail_even->next = n;
                    tail_even = n;
                }
            }
            
            n = next;
        }
        
        if (tail_odd) tail_odd->next = head_even;
        return head_odd;
    }
};
