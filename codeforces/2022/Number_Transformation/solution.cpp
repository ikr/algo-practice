#include <iostream>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using pii = pair<int, int>;

pii solve(const int x, const int y) {
    if (y % x != 0) return {0, 0};
    return {1, y / x};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int x, y;
        cin >> x >> y;

        const auto [a, b] = solve(x, y);
        cout << a << ' ' << b << '\n';
    }

    return 0;
}
