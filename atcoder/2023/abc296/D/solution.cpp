#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using lll = __int128_t;

template <typename T> constexpr lll lllof(const T x) {
    return static_cast<lll>(x);
}

template <typename T> constexpr T div_ceil(const T x, const T y) {
    return x ? (1 + (x - 1) / y) : 0;
}

ll find_X(const ll N, const ll M) {
    if (N >= M) return M;
    if (lllof(N) * N < lllof(M)) return -1;

    ll ans = LONG_LONG_MAX;

    for (ll a = 1; a * a <= M; ++a) {
        const auto b = div_ceil(M, a);
        if (a > b) break;
        if (a <= N && b <= N) ans = min(ans, a * b);
    }

    return ans == LONG_LONG_MAX ? -1LL : ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll N, M;
    cin >> N >> M;
    cout << find_X(N, M) << '\n';
    return 0;
}
