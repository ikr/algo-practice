#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr T div_ceil(const T x, const T y) {
    return x ? (1 + (x - 1) / y) : 0;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll N, M;
    cin >> N >> M;

    deque<ll> L(N);
    for (auto &l : L) cin >> l;

    const auto words_length = accumulate(cbegin(L), cend(L), 0LL);
    const auto W_e = div_ceil(words_length + N - M, M);

    ll W = LONG_LONG_MAX;
    ll cur{};
    while (!empty(L)) {
        const auto l = L.front();
        L.pop_front();

        if (cur) ++cur;
        cur += l;
        if (cur >= W_e) {
            W = min(W, cur);
            cur = 0;
        }
    }

    cout << W << '\n';
    return 0;
}
