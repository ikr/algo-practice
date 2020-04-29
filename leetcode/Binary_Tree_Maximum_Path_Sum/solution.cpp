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

int max_path_sum(int &overall_max, const TreeNode *n) {
    assert(n);
    
    const int l = n->left ? max(0, max_path_sum(overall_max, n->left)) : 0;
    const int r = n->right ? max(0, max_path_sum(overall_max, n->right)) : 0;
    
    overall_max = max(overall_max, n->val + l + r);
    return n->val + max(l, r);
}

struct Solution final {
    int maxPathSum(const TreeNode *n) const {
        int ans = INT_MIN;
        max_path_sum(ans, n);
        return ans;
    }
};
