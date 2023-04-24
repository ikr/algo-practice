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

    int t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;

        const auto ans = [&]() -> ll {
            if (n == 4) return 26;

            const auto k = (n - 5 + 1);
            return 24LL + k * (5 * 2LL + 1 + 2LL * n + 1) / 2LL + 2LL;
        }();

        cout << ans << '\n';
    }

    return 0;
}
