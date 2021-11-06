struct Solution final {
    void deleteNode(ListNode *n) const {
        const int next_value = n->next->val;
        auto next_next = n->next->next;
        
        if (next_next) deleteNode(n->next);
        else n->next = next_next;
        
        n->val = next_value;
    }
};
