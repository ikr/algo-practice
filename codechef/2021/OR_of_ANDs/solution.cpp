#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

array<set<int>, 31> bit_freqs(const vi &xs) {
    array<set<int>, 31> ans;

    for (int i = 0; i < sz(xs); ++i) {
        for (int j = 0; j <= 30; ++j) {
            if (xs[i] & (1 << j)) ans[j].insert(i);
        }
    }

    return ans;
}

int or_all(const array<set<int>, 31> &bfs) {
    int ans = 0;

    for (int i = 0; i < 31; ++i) {
        if (bfs[i].empty()) continue;
        ans |= (1 << i);
    }

    return ans;
}

vi solution(const vi &xs, const vector<pii> &queries) {
    auto bfs = bit_freqs(xs);

    vi ans{or_all(bfs)};
    ans.reserve(sz(queries) + 1);

    for (const auto [i, x] : queries) {
        for (int j = 0; j <= 30; ++j) {
            bfs[j].erase(i);
            if (x & (1 << j)) bfs[j].insert(i);
        }

        ans.push_back(or_all(bfs));
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;

        vi xs(n);
        for (auto &x : xs) cin >> x;

        vector<pii> queries(q);
        for (auto &[i, x] : queries) {
            cin >> i >> x;
            --i;
        }

        const auto ans = solution(xs, queries);
        for (const auto x : ans) cout << x << '\n';
    }

    return 0;
}
