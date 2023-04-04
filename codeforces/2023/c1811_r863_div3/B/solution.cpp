#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int level(const int n, const pii p) {
    const auto [x, y] = p;
    return min({x - 1, n - x, y - 1, n - y});
}

int min_energy(const int n, const pii pa, const pii pb) {
    return abs(level(n, pa) - level(n, pb));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        pii pa, pb;
        cin >> pa.first >> pa.second >> pb.first >> pb.second;

        cout << min_energy(n, pa, pb) << '\n';
    }

    return 0;
}
