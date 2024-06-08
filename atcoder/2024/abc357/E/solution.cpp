#include <atcoder/scc>
#include <bits/stdc++.h>
using namespace std;

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &xss) {
    for (const auto &xs : xss) os << xs << '\n';
    return os;
}

template <typename T> ostream &operator<<(ostream &os, const set<T> &xs) {
    os << '{';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << '}';
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vector<vector<int>> g(n);
    atcoder::scc_graph scc_g(n);
    for (int u = 0; u < n; ++u) {
        int v;
        cin >> v;
        --v;

        g[u].push_back(v);
        scc_g.add_edge(u, v);
    }

    const auto scc = scc_g.scc();
    map<int, int> ci_by_v;
    for (int i = 0; i < sz(scc); ++i) {
        for (const auto v : scc[i]) {
            ci_by_v.emplace(v, i);
        }
    }

    const auto n_ = sz(scc);
    set<pair<int, int>> edges_;
    for (int u = 0; u < n; ++u) {
        for (const auto v : g[u]) {
            const auto iu = ci_by_v.at(u);
            const auto iv = ci_by_v.at(v);
            if (iu != iv) edges_.emplace(iu, iv);
        }
    }

    cerr << edges_ << endl;
    return 0;
}
