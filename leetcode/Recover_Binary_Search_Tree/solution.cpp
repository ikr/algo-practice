template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}
template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}


using vi = vector<int>;
using pi = pair<int, int>;

void in_order(vi &ans, const TreeNode *n) {
    if (!n) return;
    in_order(ans, n->left);
    ans.push_back(n->val);
    in_order(ans, n->right);
}

void swap_values(TreeNode * n, const pi xy) {
    if (!n) return;
    const auto [x, y] = xy;
    if (n->val == x) n->val = y;
    else if (n->val == y) n->val = x;
    swap_values(n->left, xy);
    swap_values(n->right, xy);
}

pi misplaced(const vi &xs, const vi &ys) {
    vi ans;
    const int sz = xs.size();
    assert(xs.size() == ys.size());
    
    for (int i = 0; i != sz; ++i) {
        if (xs[i] != ys[i]) ans.push_back(xs[i]);
    }    
    
    assert(ans.size() == 2);
    return {ans[0], ans[1]};
}

struct Solution final {
    void recoverTree(TreeNode *n) const {
        vi xs;
        in_order(xs, n);
        vi ys = xs;
        sort(ys.begin(), ys.end());
        swap_values(n, misplaced(xs, ys));
    }
};
