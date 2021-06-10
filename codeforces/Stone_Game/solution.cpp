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

int min_moves(const vi &xs) {
    const auto [lo, hi] = minmax_element(cbegin(xs), cend(xs));

    int ltr_lo = -1;
    int ltr_hi = -1;
    for (int i = 0; i < sz(xs); ++i) {
        if (ltr_lo == -1 && xs[i] == *lo) {
            ltr_lo = i;
        }

        if (ltr_hi == -1 && xs[i] == *hi) {
            ltr_hi = i;
        }
    }

    const auto l = min(ltr_lo, ltr_hi);
    const auto r = max(ltr_lo, ltr_hi);

    return min({r + 1, sz(xs) - 1 - l + 1, l + 1 + sz(xs) - 1 - r + 1});
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vi xs(n);
        for (auto &x : xs) cin >> x;
        cout << min_moves(xs) << '\n';
    }

    return 0;
}
