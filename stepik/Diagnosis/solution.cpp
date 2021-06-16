#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vvi gather_children(const vi &parent) {
    vvi ans(sz(parent));
    for (int u = 1; u < sz(parent); ++u) {
        ans[parent[u]].push_back(u);
    }
    return ans;
}

vi gather_levels(const vvi &children) {
    vi ans(sz(children), 0);
    function<void(int, int)> recur;
    recur = [&](const int level, const int u) {
        ans[u] = level;
        for (const auto v : children[u]) {
            recur(level + 1, v);
        }
    };
    recur(1, 1);
    return ans;
}

vi diagnose(const vi &phab_parent, const vvi &diseases, const vvi &patients) {
    const auto ch = gather_children(phab_parent);
    const auto lvl = gather_levels(ch);
    return vi(sz(patients), 0);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vi phab_parent(n + 1, 0);
    for (int i = 2; i <= n; ++i) cin >> phab_parent[i];

    vi ic(n + 1, 0);
    for (int i = 1; i <= n; ++i) cin >> ic[i];

    int m;
    cin >> m;
    vvi diseases(m);
    for (auto &vs : diseases) {
        int cm;
        cin >> cm;
        vs.resize(cm);
        for (auto &v : vs) cin >> v;
    }

    int nq;
    cin >> nq;
    vvi patients(nq);
    for (auto &vs : patients) {
        int cq;
        cin >> cq;
        vs.resize(cq);
        for (auto &v : vs) cin >> v;
    }

    for (const auto x : diagnose(phab_parent, diseases, patients)) {
        cout << x + 1 << '\n';
    }

    return 0;
}
