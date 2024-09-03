#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr T div_ceil(const T x, const T y) {
    return x ? (1 + (x - 1) / y) : 0;
}

ll prefix_isum_in_a_rotation(const int r, const vector<ll> &ss, const int i) {
    if (i < 0) return 0LL;
    const auto n = sz(ss);
    assert(r >= 0);
    assert(r < n);

    const auto psum = [&](const int i0, const int m) -> ll {
        if (!m) return 0LL;
        return ss[i0 + m - 1] - (i0 ? ss[i0 - 1] : 0LL);
    };

    const auto m1 = min(n - r, i + 1);
    const auto m2 = (i + 1) > m1 ? (i + 1 - m1) : 0;
    return psum(r, m1) + psum(0, m2);
}

vector<ll> sums_for_each_query(const vector<ll> &xs,
                               const vector<pair<ll, ll>> &queries) {
    const ll n = sz(xs);
    vector<ll> ss(n);
    partial_sum(cbegin(xs), cend(xs), begin(ss));

    vector<ll> result;
    result.reserve(sz(queries));
    for (const auto &[l, r] : queries) {
        const auto rl = inof(l / n);
        const auto rr = inof(r / n);

        ll s{};

        if (rr - rl > 1) {
            s += ss.back() * (rr - rl - 1LL);
        }

        const auto il = inof(l % n);
        const auto ir = inof(r % n);

        if (rl == rr) {
            s += prefix_isum_in_a_rotation(rr, ss, ir) -
                 prefix_isum_in_a_rotation(rl, ss, il - 1);
        } else {
            s += ss.back() - prefix_isum_in_a_rotation(rl, ss, il - 1);
            s += prefix_isum_in_a_rotation(rr, ss, ir);
        }
        result.push_back(s);
    }
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;

        vector<ll> xs(n);
        for (auto &x : xs) cin >> x;

        vector<pair<ll, ll>> queries(q);
        for (auto &[l, r] : queries) {
            cin >> l >> r;
            --l;
            --r;
        }

        for (const auto s : sums_for_each_query(xs, queries)) {
            cout << s << '\n';
        }
    }

    return 0;
}
