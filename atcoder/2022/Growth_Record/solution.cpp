#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M, X, T, D;
    cin >> N >> M >> X >> T >> D;

    const auto w0 = T - D * X;

    const auto ans = [&]() -> int {
        if (M >= X) return T;
        return w0 + D * M;
    }();

    cout << ans << '\n';
    return 0;
}
