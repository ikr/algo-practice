#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr T div_ceil(const T x, const T y) {
    return x ? (1 + (x - 1) / y) : 0;
}

ll max_lit_up(const ll N, const ll M) {
    assert(N <= M);
    if (N == 2) return N * M / 2LL;

    const auto layers = div_ceil(N, 2LL) - 1LL;
    const auto core_area = (M - 2LL * layers) * (N % 2 ? 1LL : 2LL);
    const auto core_lit_up = (N % 2 ? 0LL : core_area / 2L);

    return N * M - core_area - layers * 2LL + core_lit_up;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll N, M;
    cin >> N >> M;
    if (N > M) swap(N, M);

    cout << max_lit_up(N, M) << '\n';
    return 0;
}
