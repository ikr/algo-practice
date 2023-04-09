#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, D;
    cin >> N >> D;

    vector<int> xs(N);
    for (auto &x : xs) cin >> x;

    const auto ans = [&]() -> int {
        for (int i = 0; i < sz(xs) - 1; ++i) {
            const auto d = xs[i + 1] - xs[i];
            if (d <= D) return xs[i + 1];
        }

        return -1;
    }();

    cout << ans << '\n';
    return 0;
}
