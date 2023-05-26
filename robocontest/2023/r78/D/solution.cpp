#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, Q;
    cin >> N >> Q;

    vector<ll> xs(N);
    for (auto &x : xs) cin >> x;

    vector<ll> ss(N);
    partial_sum(cbegin(xs), cend(xs), begin(ss));

    const auto psum = [&ss](const int i, const int j) -> ll {
        if (j < 0) return 0;
        if (i >= sz(ss)) return 0;
        return ss[j] - (i ? ss[i - 1] : 0LL);
    };

    for (int q = 1; q <= Q; ++q) {
        int l, r;
        cin >> l >> r;
        --l;
        --r;

        ll K;
        cin >> K;

        const auto cur =
            psum(0, l - 1) + K * (r - l + 1LL) + psum(r + 1, N - 1);

        cout << ((cur % 2LL == 0LL) ? "YES" : "NO") << '\n';
    }
    return 0;
}
