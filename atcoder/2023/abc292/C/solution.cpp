#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll count_divisors(const int x) {
    int ans = (x == 1) ? 1 : 2;
    const int lim = sqrt(x);

    for (int i = 2; i <= lim; ++i) {
        if (x % i) continue;
        ++ans;
        if (x / i > lim) ++ans;
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    ll ans{};
    for (int a = 1; a <= N - 1; ++a) {
        const auto b = N - a;
        ans += count_divisors(a) * count_divisors(b);
    }

    cout << ans << '\n';
    return 0;
}
