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

vll solve(const set<pair<ll, ll>> ps, const vll &s) {
    vll ans(sz(s), 0);
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

        cout << "Case #" << i << ": " << solve(ps, ss) << '\n';
    }

    return 0;
}
