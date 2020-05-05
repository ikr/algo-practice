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
    ListNode* removeElements(ListNode *n, const int x) const {
        ListNode *ans = n;
        ListNode *p = nullptr;
        ListNode *q = n;
        
        while (q) {
            if (q->val == x) {
                if (!p) {
                    q = q->next;
                    ans = q; 
                    continue;
                }
                
                p->next = q->next;
            } else p = q; 
            
            q = q->next;
        }
        
        return ans;
    }
};
