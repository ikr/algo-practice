#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        long long N, D, K;
        cin >> N >> D >> K;
        --K;

        const auto p = (gcd(N, D) == 1LL) ? N : (N / gcd(N, D));
        const auto s = K / p;
        const auto ans = (s + ((K * D) % N)) % N;
        cout << ans << '\n';
    }

    return 0;
}
