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
        int a, b, c;
        cin >> a >> b >> c;

        const auto t1 = abs(a - 1);
        const auto t2 = abs(b - c) + abs(c - 1);
        const auto ans = (t1 == t2 ? 3 : (t1 < t2 ? 1 : 2));
        cout << ans << '\n';
    }

    return 0;
}
