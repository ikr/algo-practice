using vi = vector<int>;

void recur(vi &xs, const TreeNode *n) {
    if (!n) return;
    recur(xs, n->left);
    xs.push_back(n->val);
    recur(xs, n->right);
}

struct Solution final {
    vi inorderTraversal(const TreeNode *n) {
        vi ans;
        recur(ans, n);
        return ans;
    }
};
