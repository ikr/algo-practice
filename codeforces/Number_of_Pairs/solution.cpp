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

ll pairs_num(const vi &xs, const int lo, const int hi) {
    ll ans = 0;

    for (auto it = cbegin(xs); it != cend(xs); ++it) {
        const int dlo = max(lo - *it, 0);
        const auto first = lower_bound(next(it), cend(xs), dlo);

        const int dhi = hi - *it;
        if (dhi <= 0) break;

        const auto last = upper_bound(next(it), cend(xs), dhi);
        ans += distance(first, last);
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
        int n, lo, hi;
        cin >> n >> lo >> hi;

        vi xs(n);
        for (auto &x : xs) cin >> x;

        sort(begin(xs), end(xs));
        cout << pairs_num(xs, lo, hi) << '\n';
    }

    return 0;
}
