int recur(const int max_so_far, TreeNode *n) {
    assert(!!n);
    int ans = max_so_far > n->val ? 0 : 1;

    if (n->left) {
        ans += recur(max(max_so_far, n->val), n->left);
    }

    if (n->right) {
        ans += recur(max(max_so_far, n->val), n->right);
    }

    return ans;
}

class Solution {
public:
    int goodNodes(TreeNode* n) {
        if (!n) return 0;
        return recur(n->val, n);
    }
};
