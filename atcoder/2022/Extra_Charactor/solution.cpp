#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string xs;
    string ys;
    cin >> xs >> ys;

    const auto n = min(sz(xs), sz(ys));
    const auto ans = [&]() -> int {
        for (int i = 0; i < n; ++i) {
            if (xs[i] != ys[i]) return i + 1;
        }
        return n + 1;
    }();

    cout << ans << '\n';
    return 0;
}
