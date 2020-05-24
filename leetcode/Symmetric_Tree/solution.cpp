bool match(const TreeNode *ln, const TreeNode *rn) {
    if (!ln && !rn) return true;
    if (!ln || !rn || ln->val != rn->val) return false;
    return match(ln->left, rn->right) && match(ln->right, rn->left);
}

struct Solution final {
    bool isSymmetric(const TreeNode *n) const {
        if (!n) return true;
        return match(n->left, n->right);
    }
};
