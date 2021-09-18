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

ll solve(const string &xs) {
    vi idx;

    for (int i = 0; i < sz(xs); ++i) {
        if (xs[i] == '1') {
            idx.push_back(i);
        }
    }

    ll ans = 0;

    for (int i = 0; i < sz(xs); ++i) {
        if (xs[i] == '1') continue;

        const auto it = lower_bound(cbegin(idx), cend(idx), i);
        if (it == cend(idx)) {
            ans += abs(i - idx.back());
            continue;
        }

        const auto jt = it == cbegin(idx) ? it : prev(it);
        ans += min(abs(i - *it), abs(i - *jt));
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int n;
        cin >> n;

        string xs(n, ' ');
        cin >> xs;

        cout << "Case #" << i << ": " << solve(xs) << '\n';
    }

    return 0;
}
