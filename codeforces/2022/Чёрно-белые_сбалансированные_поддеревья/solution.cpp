#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<vector<int>> gather_children(const vector<int> &ps) {
    vector<vector<int>> ch(sz(ps));
    for (int i = 1; i < sz(ps); ++i) {
        ch[ps[i]].push_back(i);
    }
    return ch;
}

vector<int> gather_leaves(const vector<vector<int>> &ch) {
    vector<int> result;
    for (int u = 0; u < sz(ch); ++u) {
        if (ch[u].empty()) result.push_back(u);
    }
    return result;
}

constexpr int cval(const char c) { return c == 'W' ? 1 : -1; }

int num_balanced(const vector<int> &ps, const string &cs) {
    const auto ch = gather_children(ps);
    vector<int> bs(sz(ps), 0);

    const auto dfs = [&](const auto &self, const int u) -> void {
        for (const auto v : ch[u]) {
            self(self, v);
            bs[u] += bs[v];
        }
        bs[u] += cval(cs[u]);
    };

    dfs(dfs, 0);
    return inof(count(cbegin(bs), cend(bs), 0));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> ps(n, -1);
        for (int i = 2; i <= n; ++i) {
            int p;
            cin >> p;
            --p;

            ps[i - 1] = p;
        }

        string cs;
        cin >> cs;
        assert(sz(cs) == n);

        cout << num_balanced(ps, cs) << '\n';
    }

    return 0;
}
