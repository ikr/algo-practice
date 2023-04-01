#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using lll = __int128_t;

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr lll lllof(const T x) {
    return static_cast<lll>(x);
}

ll find_X(const lll N, const lll M) {
    if (N >= M) return llof(N);
    if (N * N < M) return -1;

    lll hi = N * N;
    lll lo = M;

    while (lo + lllof(1) < hi) {
        const auto mid = lo + (hi - lo) / lllof(2);
        if (mid >= M) {
            hi = mid;
        } else {
            lo = mid;
        }
    }

    return llof(hi);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll N, M;
    cin >> N >> M;
    cout << find_X(N, M) << '\n';
    return 0;
}
