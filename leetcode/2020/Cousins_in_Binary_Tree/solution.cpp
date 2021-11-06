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

void cousins_depth_dfs(const pair<int, int> xy, pair<int, int> &ans, const TreeNode *n, const int depth) {
    if (!n || (ans.first > 0 && ans.second > 0)) return;
    const auto [x, y] = xy;
    
    if (
        n->left && n->right && (
            (n->left->val == x && n->right->val == y) || (n->left->val == y && n->right->val == x)
        )
    ) return;
    
    if (n->val == x) ans.first = depth;
    if (n->val == y) ans.second = depth;
    
    if(n->left) cousins_depth_dfs(xy, ans, n->left, depth + 1);
    if(n->right) cousins_depth_dfs(xy, ans, n->right, depth + 1);
}

struct Solution final {
    bool isCousins(const TreeNode *n, const int x, const int y) const {
        pair<int, int> depths{-1, -1};
        cousins_depth_dfs({x, y}, depths, n, 0);
        
        const auto [dx, dy] = depths;
        
        return dx > 0 && dy > 0 && dx == dy;
    }
};
