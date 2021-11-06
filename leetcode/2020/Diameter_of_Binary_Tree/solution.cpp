namespace {
int height(TreeNode *root) {
    if (!root) return -1;
    return max(height(root->left) + 1, height(root->right) + 1);
}
    
int max_path_length(TreeNode *root) {
    if (!root) return 0;
    
    return max({
        max_path_length(root->left), 
        max_path_length(root->right),
        2 + height(root->left) + height(root->right)
    });
}
} // namespace

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        return max_path_length(root);
    }
};
