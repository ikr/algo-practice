#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M, P;
    cin >> N >> M >> P;

    const auto ans = [&]() -> int {
        if (N < M) return 0;
        return (N - M) / P + 1;
    }();
    cout << ans << '\n';
    return 0;
}
