#include <bits/stdc++.h>
using namespace std;

using ll = long long;

static constexpr ll INF = LONG_LONG_MAX;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr T div_ceil(const T x, const T y) {
    return x ? (1 + (x - 1) / y) : 0;
}

ll max_k(const ll c, const ll d, const vector<ll> &xs) {
    if (xs[0] >= c) return INF;
    if (xs[0] * d < c) return -1;

    const auto n = sz(xs);
    vector<ll> ss(n);
    partial_sum(cbegin(xs), cend(xs), begin(ss));

    ll result{};

    for (int i = 1; i < n; ++i) {
        const auto full_cycles = c / ss[i];
        const auto r = c % ss[i];

        const auto it = lower_bound(cbegin(ss), cbegin(ss) + i + 1, r);
        if (it == cend(ss)) continue;

        if (full_cycles * (i + 1) +
                (r ? inof(distance(cbegin(ss), it)) + 1 : 0) <=
            d) {
            result = i;
        }
    }

    const auto S = ss.back();

    ll lo = n;
    ll hi = 1e16;
    const auto total_cycles = c / S;

    while (lo + 1 < hi) {
        const auto mid = lo + (hi - lo) / 2LL;
        const auto r = c % S;

        const auto it = lower_bound(cbegin(ss), cend(ss), r);
        if (it == cend(ss)) {
            hi = mid;
            continue;
        }

        if (total_cycles * (mid + 1) +
                (r ? inof(distance(cbegin(ss), it)) + 1 : 0) <=
            d) {
            lo = mid;
        } else {
            hi = mid;
        }
    }

    result = max(result, lo);
    return result;
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
