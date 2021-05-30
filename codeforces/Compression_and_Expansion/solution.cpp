#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

struct Node final {
    vector<Node *> ch;

    Node() : ch{nullptr} { assert(sz(ch) == 1); }

    ~Node() {
        for (auto p : ch) delete p;
    }
};

struct Tree final {
    Node *root;
    vector<set<Node *>> idx;

    Tree(const int x_max) : root(new Node()), idx(x_max + 2) {
        idx[1].insert(root);
    }

    ~Tree() { delete root; }

    void insert(const int x) {
        if (idx[x].empty()) cerr << "No container for " << x << endl;
        assert(!idx[x].empty());

        auto p = *cbegin(idx[x]);
        auto c = new Node();
        p->ch.push_back(c);

        idx[x].erase(cbegin(idx[x]));
        idx[x + 1].insert(p);
        idx[1].insert(c);
    }
};

Tree *build_tree(const vi &xs) {
    auto ans = new Tree(*max_element(cbegin(xs), cend(xs)));
    for (const auto x : xs) ans->insert(x);
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vi xs(n);
        for (auto &x : xs) cin >> x;

        auto tr = build_tree(xs);
        delete tr;
    }

    return 0;
}
