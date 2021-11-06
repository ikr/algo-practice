/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

namespace {
bool is_valid(const vector<int> &xs, const int i, const TreeNode *n) {
    const int sz = xs.size();
    if (i == sz) return !n;
    if (!n) return i == sz;
    if (n->val != xs[i]) return false;
    if (!n->left && !n->right) return i == sz - 1;

    const bool l = n->left ? is_valid(xs, i + 1, n->left) : false;
    const bool r = n->right ? is_valid(xs, i + 1, n->right) : false;
    
    return l || r;
}
}

struct Solution final {
    bool isValidSequence(const TreeNode *n, const vector<int> &xs) const {
        return is_valid(xs, 0, n);
    }
};
