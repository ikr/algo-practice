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
    vector<stack<Node *>> idx;

    Tree(const int x_max) : root(new Node()), idx(x_max + 2) {
        idx[1].push(root);
    }

    ~Tree() { delete root; }

    void insert(const int x) {
        if (idx[x].empty()) cerr << "No container for " << x << endl;
        assert(!idx[x].empty());

        auto p = idx[x].top();
        auto c = new Node();
        p->ch.push_back(c);

        idx[x].pop();
        idx[x + 1].push(p);
        idx[1].push(c);
    }
};

Tree *build_tree(const vi &xs) {
    auto ans = new Tree(*max_element(cbegin(xs), cend(xs)));
    for (const auto x : xs) ans->insert(x);
    return ans;
}

void print_tree(const string &prefix, const int i, const Node *p) {
    if (!p) return;

    stringstream ss;
    ss << prefix;
    if (i) {
        if (!prefix.empty()) ss << '.';
        ss << i;
    }

    if (!ss.str().empty()) cout << ss.str() << '\n';

    for (int j = 0; j < sz(p->ch); ++j) {
        print_tree(ss.str(), j, p->ch[j]);
    }
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
        print_tree("", 0, tr->root);
        delete tr;
    }

    return 0;
}
