#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

ll gauss_n(const double r) {
    ll s{};
    for (int i = 1; i <= inof(r); ++i) {
        s += inof(sqrt(r * r - doof(i) * doof(i)));
    }
    return 1 + 4 * llof(r) + 4 * s;
}

static constexpr double Eps = 0.0000001;
ll num_points(const double r) {
    return gauss_n(r + 1.0 - Eps) - gauss_n(r - Eps);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int r;
        cin >> r;
        cout << num_points(r) << '\n';
    }

    return 0;
}
