#include <atcoder/dsu>
#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M;
    cin >> N >> M;

    vector<vector<int>> g(N);
    atcoder::dsu cs(N);

    for (int i = 1; i <= M; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;

        g[u].push_back(v);
        g[v].push_back(u);
        cs.merge(u, v);
    }

    bool yes = true;
    if (sz(cs.groups()) == 1) {
        map<int, int> fs;
        for (int u = 0; u < N; ++u) {
            ++fs[sz(g[u])];
        }

        yes = (sz(fs) == (N > 2 ? 2 : 1) && fs.count(1) && fs.at(1) == 2 &&
               fs[2] == (N - 2));
    } else {
        yes = false;
    }

    cout << (yes ? "Yes" : "No") << '\n';
    return 0;
}
