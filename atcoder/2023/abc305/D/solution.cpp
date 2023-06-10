#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

optional<pii> intersection(const pii ab, const pii cd) {
    const auto [a, b] = ab;
    const auto [c, d] = cd;

    assert(a <= b);
    assert(c <= d);
    if (d < a || c > b) return nullopt;

    array<int, 4> xs{a, b, c, d};
    sort(begin(xs), end(xs));
    return pii{xs[1], xs[2]};
}

ll sleep_time(const vector<pii> &AB, const vector<ll> &ss, const pii lr) {
    const auto n = sz(AB);

    const auto potentially_intersecting_index = [&](const int x) -> int {
        const auto it = lower_bound(cbegin(AB), cend(AB), pii{x, x});
        if (it == cend(AB)) return n - 1;

        const auto [a, b] = *it;
        if (a == x) return inof(it - cbegin(AB));

        assert(it != cbegin(AB));
        return inof(it - cbegin(AB)) - 1;
    };

    const auto [l, r] = lr;
    const auto il = potentially_intersecting_index(l);
    const auto ir = potentially_intersecting_index(r);

    ll ans{};
    for (int j : {il, ir}) {
        const auto x = intersection(AB[j], lr);
        if (x) ans += x->second - x->first;
    }
    if (il + 1 < ir) ans += ss[ir - 1] - ss[il];
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vector<int> xs(n);
    for (auto &x : xs) cin >> x;

    vector<pii> AB{{0, 0}};
    AB.reserve(n / 2);

    for (int i = 1; i + 1 < n; i += 2) {
        AB.emplace_back(xs[i], xs[i + 1]);
    }

    vector<ll> ss(sz(AB), 0LL);
    for (int i = 1; i < sz(ss); ++i) {
        ss[i] = ss[i - 1] + AB[i].second - AB[i].first;
    }

    int Q;
    cin >> Q;

    for (int q = 1; q <= Q; ++q) {
        int l, r;
        cin >> l >> r;

        cout << sleep_time(AB, ss, {l, r}) << '\n';
    }

    return 0;
}
