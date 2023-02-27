#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<int> construct_permutation(const vector<vector<int>> &g) {
    const auto n = sz(g);
    vector<int> ideg(n, 0);

    for (int u = 0; u < n; ++u) {
        for (const auto v : g[u]) {
            ++ideg[v];
        }
    }

    set<pii> iq;
    for (int u = 0; u < n; ++u) iq.emplace(ideg[u], u);

    vector<int> pref;

    while (sz(pref) < n) {
        if (iq.empty()) return {};
        const auto [id, u] = *cbegin(iq);
        if (id != 0) return {};
        iq.erase(cbegin(iq));
        if (!iq.empty() && cbegin(iq)->first == 0) return {};

        pref.push_back(u);

        for (const auto v : g[u]) {
            const auto jd = ideg[v];
            --ideg[v];

            const auto jt = iq.find(pii{jd, v});
            iq.erase(jt);
            iq.emplace(ideg[v], v);
        }
    }

    return pref;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M;
    cin >> N >> M;

    vector<vector<int>> g(N);
    for (int i = 1; i <= M; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;

        g[u].push_back(v);
    }

    const auto ans = construct_permutation(g);

    if (ans.empty()) {
        cout << "No\n";
    } else {
        cout << "Yes\n";
        for (auto i = ans.cbegin(); i != ans.cend(); ++i) {
            if (i != ans.cbegin()) cout << ' ';
            const auto a = (*i) + 1;
            cout << a;
        }
        cout << '\n';
    }

    return 0;
}
