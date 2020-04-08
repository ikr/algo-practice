/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        auto p1 = head;
        auto p2 = head;
        
        while (p2) {
            p2 = p2->next;
            
            if (p2) {
                p1 = p1->next;
                p2 = p2->next;
            }
        }
        
        return p1;
    }
};
