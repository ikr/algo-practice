#include <climits>
#include <iostream>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using ll = long long;

ll min_ops(const ll X, const ll A, const ll D, const ll N) {
    const auto lo = min(A, A + (N - 1) * D);
    if (X <= lo) return lo - X;

    const auto hi = max(A, A + (N - 1) * D);
    if (hi <= X) return X - hi;

    const ll m = abs(D);
    const ll z = ((A % m) + m) % m;

    ll result = LONG_LONG_MAX;
    for (ll k = 0; k < m; ++k) {
        const auto p = (((X + k) % m) + m) % m;
        if (lo <= X + k && X + k <= hi && p == z) {
            result = min(result, k);
        }

        const auto q = (((X - k) % m) + m) % m;
        if (lo <= X - k && X - k <= hi && q == z) {
            result = min(result, k);
        }
    }
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll X, A, D, N;
    cin >> X >> A >> D >> N;

    cout << min_ops(X, A, D, N) << '\n';
    return 0;
}
