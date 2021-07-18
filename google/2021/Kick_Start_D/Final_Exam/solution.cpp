#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

ll closest_to(const pair<ll, ll> &ab, const ll x) {
    const auto [a, b] = ab;

    if (x <= a) return a;
    if (b <= x) return b;

    assert(a < x && x < b);
    return x;
}

using Iter = set<pair<ll, ll>>::const_iterator;

void puncture_out(set<pair<ll, ll>> &ps, const Iter it, const ll x) {
    const auto [a, b] = *it;
    const auto c = closest_to(*it, x);

    ps.erase(it);

    if (a == b) {
        assert(c == a);
    } else if (c == a) {
        ps.emplace(a + 1, b);
    } else if (c == b) {
        ps.emplace(a, b - 1);
    } else {
        assert(a < c && c < b);
        ps.emplace(a, c - 1);
        ps.emplace(c + 1, b);
    }
}

vll solve(set<pair<ll, ll>> ps, const vll &s) {
    vll ans(sz(s), 0);

    for (int i = 0; i < sz(s); ++i) {
        const auto jt = [&]() {
            const auto x = ps.lower_bound({s[i], 0});
            return x == cend(ps) ? prev(x) : x;
        }();
        const auto it = jt == cbegin(ps) ? jt : prev(jt);

        const auto x = closest_to(*it, s[i]);
        const auto y = closest_to(*jt, s[i]);

        if (abs(s[i] - x) <= abs(s[i] - y)) {
            ans[i] = x;
            puncture_out(ps, it, x);
        } else {
            ans[i] = y;
            puncture_out(ps, jt, y);
        }
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int n, m;
        cin >> n >> m;

        set<pair<ll, ll>> ps;
        for (int j = 0; j < n; ++j) {
            ll a, b;
            cin >> a >> b;
            ps.emplace(a, b);
        }

        vll ss(m);
        for (auto &s : ss) cin >> s;

        cout << "Case #" << i << ": " << solve(move(ps), ss) << '\n';
    }

    return 0;
}
