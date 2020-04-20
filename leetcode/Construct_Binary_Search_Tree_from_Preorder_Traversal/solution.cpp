/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

TreeNode* build(vector<int> &preorder, const int lo, const int hi) {
    if (preorder.empty() || preorder.front() < lo || preorder.front() > hi) return nullptr;
    
    TreeNode *ans = new TreeNode(preorder.front());
    preorder.erase(preorder.cbegin());
    
    ans->left = build(preorder, lo, ans->val);
    ans->right = build(preorder, ans->val, hi);
    
    return ans;
}

class Solution {
public:
    TreeNode* bstFromPreorder(vector<int> &preorder) {
        return build(preorder, INT_MIN, INT_MAX);
    }
};
