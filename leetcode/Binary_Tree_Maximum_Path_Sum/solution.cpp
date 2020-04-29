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

optional<int> optmax(const optional<int> x, const optional<int> y) {
    const int ans = max(x ? *x : INT_MIN, y ? *y : INT_MIN);
    return ans == INT_MIN ? nullopt : optional<int>{ans};
}

optional<int> operator+(const optional<int> x, const optional<int> y) {
    if (x && y) return *x + *y;
    if (x) return *x;
    if (y) return *y;
    return nullopt;
}

optional<int> max_leaf_path_sum(TreeNode *n) {
    if (!n) return nullopt;
    return optional<int>{n->val} + optmax(max_leaf_path_sum(n->left), max_leaf_path_sum(n->right));
} 


optional<int> max_path_sum(TreeNode *n) {
    if (!n) return nullopt;
    
    return optmax(
        optmax(
            optional<int>(n->val),
            optional<int>(n->val) + max_leaf_path_sum(n->left) + max_leaf_path_sum(n->right)
        ),
        
        optmax(
            max_path_sum(n->left),
            max_path_sum(n->right)
        )
    );
}

struct Solution final {
    int maxPathSum(TreeNode *r) const {
        const auto ans = max_path_sum(r);
        return ans ? *ans : 0;
    }
};
