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

static constexpr ll INF = 1e18;

ll min_ops_01(const array<ll, 3> &a) {
    const auto d = a[1] - a[0];
    const auto target = a[1] + d;
    return target > a[2] ? target - a[2] : INF;
}

ll min_ops_12(const array<ll, 3> &a) {
    const auto d = a[2] - a[1];
    const auto target = a[1] - d;
    return target > a[0] ? target - a[0] : INF;
}

ll min_ops_02(array<ll, 3> a, const bool bias_left) {
    ll adjustment = 0;
    if ((a[2] - a[0]) % 2LL) {
        if (bias_left) {
            ++a[0];
        } else {
            ++a[2];
        }
        adjustment = 1LL;
    }

    const auto d = (a[2] - a[0]) / 2LL;
    const auto target = a[0] + d;
    return target > a[1] ? (target - a[1] + adjustment) : INF;
}

ll min_ops(const array<ll, 3> &a) {
    if (a[2] - a[1] == a[1] - a[0]) return 0;
    return min({min_ops_01(a), min_ops_12(a), min_ops_02(a, true),
                min_ops_02(a, false)});
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    array<ll, 3> a;
    for (auto &x : a) cin >> x;

    cout << min_ops(a) << '\n';
    return 0;
}
