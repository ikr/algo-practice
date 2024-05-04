#include <atcoder/dsu>
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, m;
    cin >> n >> m;

    vector<int> cs(m);
    vector<vector<int>> vss(m);

    for (int i = 0; i < m; ++i) {
        int k;
        cin >> k >> cs[i];

        vector<int> vs(k);
        for (auto &v : vs) {
            cin >> v;
            --v;
        }
        vss[i] = vs;
    }

    vector<int> idx(m);
    iota(begin(idx), end(idx), 0);
    sort(begin(idx), end(idx),
         [&](const int i, const int j) { return cs[i] < cs[j]; });

    atcoder::dsu dsu(n);
    ll result{};
    for (const auto i : idx) {
        const auto u = vss[i][0];
        for (int j = 1; j < sz(vss[i]); ++j) {
            const auto v = vss[i][j];
            if (dsu.leader(u) != dsu.leader(v)) {
                dsu.merge(u, v);
                result += cs[i];
            }
        }
    }

    if (sz(dsu.groups()) != 1) result = -1;
    cout << result << '\n';
    return 0;
}
