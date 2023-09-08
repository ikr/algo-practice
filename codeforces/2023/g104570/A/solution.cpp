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
        int a, b, c, n;
        cin >> a >> b >> c >> n;

        const auto ans = [&]() -> bool {
            auto r = n;

            const auto hs = r / 100;
            r -= min(c, hs) * 100;

            const auto ds = r / 10;
            r -= min(b, ds) * 10;

            r -= min(a, r);
            return r == 0;
        }();
        cout << (ans ? "YES" : "NO") << '\n';
    }

    return 0;
}
