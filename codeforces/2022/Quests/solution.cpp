#include <bits/stdc++.h>
using namespace std;

using ll = long long;

static constexpr ll INF = LONG_LONG_MAX;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll max_k(const ll c, const ll d, const vector<ll> &xs) {
    if (xs[0] * d < c) return -1;

    const auto n = sz(xs);
    vector<ll> ss(n);
    partial_sum(cbegin(xs), cend(xs), begin(ss));

    const auto safe_sum = [&](const ll i) -> ll {
        if (i < 0LL) return 0;
        if (i > n - 1LL) return ss.back();
        return ss[i];
    };

    if (safe_sum(d - 1) >= c) return INF;

    ll lo = 0LL;
    ll hi = d + 1;
    while (lo + 1 < hi) {
        const auto k = lo + (hi - lo) / 2LL;
        const auto [q, r] = lldiv(d, k + 1);

        if (q * safe_sum(k) + safe_sum(r - 1) >= c) {
            lo = k;
        } else {
            hi = k;
        }
    }

    return lo;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        ll c;
        cin >> c;

        ll d;
        cin >> d;

        vector<ll> xs(n);
        for (auto &x : xs) cin >> x;
        sort(rbegin(xs), rend(xs));

        const auto result = max_k(c, d, xs);
        if (result < 0) {
            cout << "Impossible\n";
        } else if (result == INF) {
            cout << "Infinity\n";
        } else {
            cout << result << '\n';
        }
    }

    return 0;
}
