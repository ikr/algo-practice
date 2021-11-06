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

void lsum_dfs(int &ans, const TreeNode *n) {
    if (!n) return;
    
    if (n->left) {
        if (!n->left->left && !n->left->right) ans += n->left->val;
        lsum_dfs(ans, n->left);
    }
    
    if (n->right) lsum_dfs(ans, n->right);
}

struct Solution {
    int sumOfLeftLeaves(const TreeNode *n) const {
        int ans = 0;
        lsum_dfs(ans, n);        
        return ans;
    }
};
