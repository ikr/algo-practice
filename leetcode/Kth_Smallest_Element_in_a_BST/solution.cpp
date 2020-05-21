void discover_value(vector<int> &heap, const int k, const int x) {
    if (heap.size() == k) {
        if (heap.front() > x) {
            pop_heap(heap.begin(), heap.end());
            heap.pop_back();
        } else return;
    }

    heap.push_back(x);
    push_heap(heap.begin(), heap.end());
}

void dfs(vector<int> &heap, const int k, const TreeNode *n) {
    if (!n) return;
    discover_value(heap, k, n->val);
    dfs(heap, k, n->left);
    dfs(heap, k, n->right);
}

struct Solution final {
    int kthSmallest(const TreeNode *n, const int k) {
        vector<int> heap;
        dfs(heap, k, n);
        return heap.front();
    }
};
