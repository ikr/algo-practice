#include <atcoder/dsu>
#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vi degrees(const int n, const vector<pii> &es) {
    vi ans(n, 0);
    for (const auto [u, v] : es) {
        ++ans[u];
        ++ans[v];
    }
    sort(begin(ans), end(ans));
    return ans;
}

vi component_sizes(const int n, const vector<pii> &es) {
    atcoder::dsu dsu(n);
    for (const auto [u, v] : es) {
        dsu.merge(u, v);
    }

    const auto cs = dsu.groups();
    vi ans(sz(cs), 0);
    transform(cbegin(cs), cend(cs), begin(ans),
              [](const auto &c) { return sz(c); });
    sort(begin(ans), end(ans));
    return ans;
}

bool are_same(const int n, const vector<pii> &e1, const vector<pii> &e2) {
    return component_sizes(n, e1) == component_sizes(n, e2) &&
           degrees(n, e1) == degrees(n, e2);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, m;
    cin >> n >> m;

    vector<pii> e1(m);
    for (auto &[u, v] : e1) {
        cin >> u >> v;
        --u;
        --v;
    }

    vector<pii> e2(m);
    for (auto &[u, v] : e2) {
        cin >> u >> v;
        --u;
        --v;
    }

    cout << (are_same(n, e1, e2) ? "Yes" : "No") << '\n';
    return 0;
}
